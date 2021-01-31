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
	mX = g_mPosit.x;
	mY = Camera::GetInstance()->GetY()+g_mPosit.y; //이거 알아내는데 한세월;;

	float Angle = Math::GetAngle(mPlayer->GetX() + 40, mPlayer->GetY() + 45, mX, mY);
	float Vec = mPlayer->GetSkill()->GetQPower();

	for (int i = 0; i < 20; i++) {

		trajecLine[i].x = mPlayer->GetX() + 40 + Vec * i * cosf(Angle);
		trajecLine[i].y = mPlayer->GetY() + 45 - Vec * i * sinf(Angle) + 0.58 * i * 0.58 * i;
	}
}

void Aim::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mX -16-Camera::GetInstance()->GetX(), mY - 16-Camera::GetInstance()->GetY(), mFrameX, mFrameY);
	
	HBRUSH newBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	for (int i = 1; i < 20; i++)
		REllipse(hdc, RectMake(trajecLine[i].x - 2 - Camera::GetInstance()->GetX(), trajecLine[i].y - 2 - Camera::GetInstance()->GetY(), 5, 5));
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);

}

void Aim::Off()
{
	mX = WINSIZEX + 200;
	
}
