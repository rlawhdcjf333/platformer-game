#include "MovingShell.h"
#include "pch.h"
#include "Camera.h"
#include "Image.h"

void MovingShell::Init()
{
	mImage=ImageManager::GetInstance()->FindImage(L"GreenShell");
	mRadius = 150;

	mY = 60;
	mW = mImage->GetFrameWidth();
	mH = mImage->GetFrameHeight();
	
	mAngle = 0;

	//센터
	mRc = RectMake(620, 340- mRadius, mW, mH);
	mRcList.push_back(mRc);
	
	//좌측
	mRc = RectMake(290, 60- mRadius, mW, mH);
	mRcList.push_back(mRc);

	//우측
	mRc = RectMake(970, 60- mRadius, mW, mH);
	mRcList.push_back(mRc);
}

void MovingShell::Render(HDC hdc)
{

	for(RECT elem : mRcList)
	mImage->Render(hdc, elem.left-Camera::GetInstance()->GetX(), elem.top-Camera::GetInstance()->GetY());
	
}

void MovingShell::Release()
{
}

void MovingShell::Update()
{
	mAngle = Math::GetAngle(620, 340, mRcList[0].left, mRcList[0].top);
	mRcList[0].left = 620 + mRadius * cosf(mAngle-0.01*PI/2);
	mRcList[0].top = 340 - mRadius * sinf(mAngle-0.01*PI/2);
	mRcList[0] = RectMake(mRcList[0].left, mRcList[0].top, mW, mH);

	mAngle = Math::GetAngle(290, 60, mRcList[1].left, mRcList[1].top);
	mRcList[1].left = 290 + mRadius * cosf(mAngle - 0.01 * PI/2);
	mRcList[1].top = 60 - mRadius * sinf(mAngle - 0.01 * PI/2);
	mRcList[1] = RectMake(mRcList[1].left, mRcList[1].top, mW, mH);
	
	mAngle = Math::GetAngle(970, 60, mRcList[2].left, mRcList[2].top);
	mRcList[2].left = 970 + mRadius * cosf(mAngle - 0.01 * PI/2);
	mRcList[2].top = 60 - mRadius * sinf(mAngle - 0.01 * PI/2);
	mRcList[2] = RectMake(mRcList[2].left, mRcList[2].top, mW, mH);



}
