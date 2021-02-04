#include "pch.h"
#include "Aim.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "Skill.h"

void Aim::Init(Player* playerPtr)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Aim");
	mFrameX = 0;
	mFrameY = 0;

	mPlayer = playerPtr;
}

void Aim::On()
{
	mX = g_mPosit.x; //ī�޶� ���� �̵��� �ϹǷ�(==ī�޶� x��ǥ ���� ����) ���� �����ǥ�� ���� ����� ����.
	mY = Camera::GetInstance()->GetY()+g_mPosit.y; //Aim y ��ǥ�� ī�޶�κ��� ���� �����ǥ.

	mAngle = Math::GetAngle(mPlayer->GetX() + 40, mPlayer->GetY() + 45, mX, mY);
	float Vec = mPlayer->GetSkill()->GetQPower();

	for (int i = 0; i < 20; i++) { //����ü ���� ź�� ���� ������Ʈ

		trajecLine[i].x = (mPlayer->GetX() + 40) + Vec * i * cosf(mAngle); // x��ǥ 1������ ������ i�� ���Ͽ� �����Ѵ�. ���л�� C�� �÷��̾� ��Ʈ�� ��� ��
		trajecLine[i].y = (mPlayer->GetY() + 45) - Vec * i * sinf(mAngle) + 0.5 * 0.58 * i * i; //��������, �ٸ� �߷��� ���ӵǰ� �����Ƿ� ���� ������ 0.58*i
	}
}

void Aim::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mX -16-Camera::GetInstance()->GetX(), mY - 16-Camera::GetInstance()->GetY(), mFrameX, mFrameY);
	
	HBRUSH newBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	for (int i = 1; i < 20; i++) //ź�� ���� ���
		REllipse(hdc, RectMake(trajecLine[i].x - 2 - Camera::GetInstance()->GetX(), trajecLine[i].y - 2 - Camera::GetInstance()->GetY(), 5, 5));
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);

}

void Aim::Off()
{
	mX = WINSIZEX + 200;
	
}
