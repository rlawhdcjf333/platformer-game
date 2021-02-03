#include "Wind.h"
#include "Image.h"
#include "Player.h"

void Wind::Init(float x, float y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Wind");

	mX = x;
	mY = y;
	mW = mImage->GetFrameWidth();
	mH = mImage->GetFrameHeight();



	mFrameX = 0;
	mFrameY = 0;
	mAlpha = 0;


	mRc = RectMake(mX, mY, mW, mH);

}

void Wind::Update()
{
	mX +=1;
	mY -= 3*sin(2*PI*mX/200);

	RotationMatrix();

	if (mX > WINSIZEX) { mX = -mW; mY = -1 * Random::GetInstance()->RandInt(850, 2200); }

	if (mAlpha > 0.8f) mAlpha = 0.1;

	mFrameCount++;
	if (mFrameCount > 5) { mFrameCount = 0; mFrameX++, mAlpha += 0.035f; }
	
	if (mFrameX > mImage->GetFrameX()-1) { mFrameX = 0, mFrameY++; }
	if (mFrameY > mImage->GetFrameY()-1) { mFrameY = 0; }

}

void Wind::Render(HDC hdc)
{
	if(mY>Camera::GetInstance()->GetY() and mY<Camera::GetInstance()->GetY()+720) //개별 클리핑
	mImage->AlphaScaleFrameRender(hdc, mX, mY - Camera::GetInstance()->GetY(), mFrameX, mFrameY, 165, 105, mAlpha);

}

void Wind::RotationMatrix() //2차원 좌표계 회전 변환 2-D coordinates rotation transform
{
	if (mPlayer->GetY() < -850 and mPlayer->GetY() > -2200) {
		float Angle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
		mY -= 1.2 * sinf(Angle);

		if(mPlayer->GetX()>mX)
		mX += 1.2 * cosf(Angle);
	}
}
