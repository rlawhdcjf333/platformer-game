#include "pch.h"
#include "WitchCat.h"
#include "Image.h"
#include "GreenShell.h"
#include "Physics.h"

void WitchCat::Init(float X, float Y)
{
	Unit::Init(L"WitchCat", X, Y);

	mStunE = ImageManager::GetInstance()->FindImage(L"Stun");

	mFrameCount = 0;
	mVec = 0;

	if (X < WINSIZEX / 2) mLocation = Location::Left;
	if (X > WINSIZEX / 2) mLocation = Location::Right;

	switch (mLocation) {

	case Location::Left:
		mStatus = Status0::rightIdle;
		break;

	case Location::Right:
		mStatus = Status0::leftIdle;
		break;
	}
}

void WitchCat::Render(HDC hdc)
{
	mImage->ScaleFrameRender(hdc, mRc.left - Camera::GetInstance()->GetX(), mRc.top - Camera::GetInstance()->GetY(), mFrameX, mFrameY, 100, 100);
	for (GreenShell*& elem : mGreenShellList) {
		if (elem != NULL) elem->Render(hdc);
	}

	if (mLocation==Location::Left and mStatus == Status0::rightHit) {
		mStunE->ScaleFrameRender(hdc, mX+40, mY - Camera::GetInstance()->GetY(), mFrameCount/2%5, 0, 50, 30);
	}


	if (mLocation == Location::Right and mStatus == Status0::leftHit) {

		mStunE->ScaleFrameRender(hdc, mX+20, mY - Camera::GetInstance()->GetY(), mFrameCount/2%5, 0, 50, 30);
	}
}

void WitchCat::Release()
{
	for (GreenShell*& elem : mGreenShellList) {
		SafeDelete(elem);
	}

}

void WitchCat::Update()
{
	switch (mLocation) {

	case Location::Left:
		if (mFrameCount == 0 and mFrameX == 7) {
			if (mFrameY == 3) {
				for (int i = 0; i < 3; i++) {
					GreenShell* mGreenShell = new GreenShell();
					mGreenShell->SetXY(150, -370);
					mGreenShell->Init(Random::GetInstance()->RandInt(20, 25), PI * Random::GetInstance()->RandInt(10, 20) / 100);
					mGreenShellList.push_back(mGreenShell);
				}
			}
		}

		break;

	case Location::Right:
		if (mFrameCount == 0 and mFrameX == 7) {
			if (mFrameY == 0) {
				for (int i = 0; i < 3; i++) {
					GreenShell* mGreenShell = new GreenShell();
					mGreenShell->SetXY(1090, -540);
					mGreenShell->Init(Random::GetInstance()->RandInt(20, 25), PI * Random::GetInstance()->RandInt(80, 90) / 100);
					mGreenShellList.push_back(mGreenShell);
				}
			}
		}
		break;
	}
	
	for (GreenShell*& elem : mGreenShellList) {
		if (elem != NULL)
			elem->Update();
	}

	for (GreenShell*& elem : mGreenShellList)
		if (elem->GetRc().top > -270) {
			SafeDelete(elem);
		}

	for (int i = 0; i < mGreenShellList.size(); i++) {
		if (mGreenShellList[i] == NULL) {
			mGreenShellList.erase(mGreenShellList.begin() + i);
			i--;
		}
	}

	Physics::GetInstance()->WitchCatHit();

	mFrameCount++;
	StatusSwitch();

}

void WitchCat::StatusSwitch()
{
	switch (mStatus) {

	case Status0::leftThrow:
		mFrameY = 0;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 9) { mFrameX = 0; mStatus = Status0::leftIdle; }
		break;
	case Status0::leftIdle:
		mFrameY = 1;
		if(mFrameCount>20) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 5) { mFrameX = 0; mStatus = Status0::leftThrow; }
		break;
	case Status0::leftHit:
		mFrameY = 2;
		mFrameX = 0;
		if (mFrameCount > 350) mStatus = Status0::leftIdle;
		break;
	case Status0::rightThrow:
		mFrameY = 3;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 9) { mFrameX = 0; mStatus = Status0::rightIdle; }
		break;
	case Status0::rightIdle:
		mFrameY = 4;
		if (mFrameCount > 20) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 5) { mFrameX = 0; mStatus = Status0::rightThrow; }
		break;
		break;
	case Status0::rightHit:
		mFrameY = 5;
		mFrameX = 0;
		if (mFrameCount > 350) mStatus = Status0::rightIdle;
		break;

	}
}
