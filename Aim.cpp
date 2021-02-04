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
	mX = g_mPosit.x; //카메라가 상하 이동만 하므로(==카메라 x좌표 변동 없음) 굳이 상대좌표를 구할 까닭이 없음.
	mY = Camera::GetInstance()->GetY()+g_mPosit.y; //Aim y 좌표가 카메라로부터 갖는 상대좌표.

	mAngle = Math::GetAngle(mPlayer->GetX() + 40, mPlayer->GetY() + 45, mX, mY);
	float Vec = mPlayer->GetSkill()->GetQPower();

	for (int i = 0; i < 20; i++) { //투사체 예측 탄도 궤적 업데이트

		trajecLine[i].x = (mPlayer->GetX() + 40) + Vec * i * cosf(mAngle); // x좌표 1프레임 변량을 i에 대하여 적분한다. 적분상수 C는 플레이어 렉트의 가운데 값
		trajecLine[i].y = (mPlayer->GetY() + 45) - Vec * i * sinf(mAngle) + 0.5 * 0.58 * i * i; //마찬가지, 다만 중력은 가속되고 있으므로 순간 변량이 0.58*i
	}
}

void Aim::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mX -16-Camera::GetInstance()->GetX(), mY - 16-Camera::GetInstance()->GetY(), mFrameX, mFrameY);
	
	HBRUSH newBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	for (int i = 1; i < 20; i++) //탄도 궤적 출력
		REllipse(hdc, RectMake(trajecLine[i].x - 2 - Camera::GetInstance()->GetX(), trajecLine[i].y - 2 - Camera::GetInstance()->GetY(), 5, 5));
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);

}

void Aim::Off()
{
	mX = WINSIZEX + 200;
	
}
