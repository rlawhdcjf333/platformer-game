#include "pch.h"
#include "Grendel.h"
#include "Image.h"

void Grendel::Init(float x, float y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Grendel");
	mX = x;
	mY = y;
	mFrameX = 0;
	mFrameY = 0;
	mAlpha = 1;
}

void Grendel::Update()
{
	mFrameCount++; mAlpha -= 0.0066f;
	if (mFrameCount > 30) {
		mFrameX++; mFrameCount = 0;
	}
	if (mFrameX > 2) mFrameX = 2;
}

void Grendel::Render(HDC hdc)
{
	mImage->AlphaScaleFrameRender(hdc, mX - Camera::GetInstance()->GetX(), mY - Camera::GetInstance()->GetY(), mFrameX, mFrameY,180,300, mAlpha);
}
