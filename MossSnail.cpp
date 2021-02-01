#include "pch.h"
#include "MossSnail.h"
#include "Image.h"

void MossSnail::Init(float X, float Y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"MossSnail");
	mVec = 1;
	mAngle = 0;
	mY = -2500; //카메라 클리핑 기준선  Camera clipping line

	mRc = RectMake(270, -2160 - 120 - 38, 40, 40);
	mStruct = { mRc, 270 };
	mStructList.push_back(mStruct);

	mRc = RectMake(805, -2160 - 230 - 38, 40, 40);
	mStruct = { mRc, 805 };
	mStructList.push_back(mStruct);

	mRc = RectMake(630, -2160 - 470 - 38, 40, 40);
	mStruct = { mRc, 630 };
	mStructList.push_back(mStruct);

	mRc = RectMake(100, -2160 - 560 - 38, 40, 40);
	mStruct = { mRc, 100 };
	mStructList.push_back(mStruct);
	

	mStatus = Status2::rightMove;
}

void MossSnail::Render(HDC hdc)
{
	for(RcAndRange& const elem : mStructList) //복사 비용이 너무 크므로 const 포인터(&)... due to the compiler complaining about a large amount of copy data
	mImage->ScaleFrameRender(hdc, elem.rc.left-Camera::GetInstance()->GetX(), elem.rc.top-Camera::GetInstance()->GetY(), mFrameX, mFrameY, 40, 40);

}

void MossSnail::Release()
{
}

void MossSnail::Update()
{
	for (RcAndRange& const elem : mStructList) { //마찬가지 same with above 
		if (elem.rc.right > elem.rightend) mStatus = Status2::leftMove;
		if (elem.rc.left < elem.leftend) mStatus = Status2::rightMove;
	}

	mFrameCount++;
	StatusSwitch();

	for (RcAndRange& elem : mStructList) { 

		elem.rc.left += mVec * cosf(mAngle);
		elem.rc = RectMake(elem.rc.left, elem.rc.top, 40, 40);
	}


}

void MossSnail::StatusSwitch()
{
	switch (mStatus) {

	case Status2::leftMove:
		mFrameY = 0; mAngle = PI;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 5) { mFrameX = 0; }
		break;
	case Status2::rightMove:
		mFrameY = 1; mAngle = 0;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 5) { mFrameX = 0;}
		break;
	}
}
