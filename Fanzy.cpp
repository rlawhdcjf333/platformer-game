#include "Fanzy.h"
#include "Image.h"
#include "Camera.h"

void Fanzy::Init(float X, float Y)
{
	mImage1 = ImageManager::GetInstance()->FindImage(L"InvisibleRect");

	mRc = RectMake(1140, -370-2160, 50, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(240, -730 - 2160, 50, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(240, -650 - 2160, 50, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(1040, -490 - 2880, 50, 10);
	mRcList.push_back(mRc);



	Unit::Init(L"Fanzy", 1080, -2880-60);

}

void Fanzy::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRc.left-Camera::GetInstance()->GetX(), mRc.top-Camera::GetInstance()->GetY(),mFrameX,mFrameY);

	if (mInvisibility == true) {
		for (RECT elem : mRcList)
			mImage1->AlphaRender(hdc, elem.left-Camera::GetInstance()->GetX(), elem.top-Camera::GetInstance()->GetY(), (float)mFrameX/12);
		
	}

}

void Fanzy::Release()
{
}

void Fanzy::Update()
{
	mFrameCount++;
	if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
	if (mFrameX > 12) mFrameX = 0;

	if (mFrameX > 6) mInvisibility = true;
	else mInvisibility = false;

}
