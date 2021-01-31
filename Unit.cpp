#include "pch.h"
#include "Unit.h"
#include "image.h"

void Unit::Move()
{
	mX += mVec * cosf(mAngle);
	mY -= mVec * sinf(mAngle);
	mRc = RectMake(mX, mY, mW, mH);
}

void Unit::Init(wstring LFileName, float X, float Y)
{
	mImage = ImageManager::GetInstance()->FindImage(LFileName);
	mW = mImage->GetFrameWidth();
	mH = mImage->GetFrameHeight();

	mX = X;
	mY = Y;
	

	mRc = RectMake(mX, mY, mW, mH);
}

void Unit::Render(HDC hdc, int ResizeX, int ResizeY)
{
	mImage->AlphaScaleFrameRender(hdc, mRc.left-Camera::GetInstance()->GetX(),
		mRc.top-Camera::GetInstance()->GetY(), mFrameX, mFrameY, ResizeX, ResizeY, mAlpha);
}
