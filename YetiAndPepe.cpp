#include "pch.h"
#include "YetiAndPepe.h"
#include "Image.h"
#include "BlueShell.h"
#include "Physics.h"

void YetiAndPepe::Init(float X, float Y)
{

	Unit::Init(L"YetiAndPepe", X,Y);
	mStatus = Status1::leftIdle;
}

void YetiAndPepe::Render(HDC hdc)
{
	mImage->ScaleFrameRender(hdc, mRc.left - Camera::GetInstance()->GetX(), mRc.top - Camera::GetInstance()->GetY(), mFrameX, mFrameY, 250, 250);

	for (BlueShell* elem : mBlueShellList) {
		if(elem!=NULL) elem->Render(hdc);
	}
}

void YetiAndPepe::Release()
{
	for (BlueShell*& elem : mBlueShellList) {
		SafeDelete(elem);
	}
	
}

void YetiAndPepe::Update()
{
	mFrameCount++;
	StatusSwitch();

	if (mFrameX == 4 and mFrameY == 1) {
		if (mFrameCount == 0) {
			for (int i = 0; i < 10; i++) {

				BlueShell* mBlueShell = new BlueShell();
				mBlueShell->SetXY(930, -1760 - 25);
				mBlueShell->Init(Random::GetInstance()->RandInt(20, 25), PI * Random::GetInstance()->RandInt(40, 75) / 100);
				mBlueShellList.push_back(mBlueShell);
			}
		}
	}

	for (BlueShell*& elem : mBlueShellList) {
		if(elem!=NULL)
		elem->Update();
	}

	for (BlueShell*& elem : mBlueShellList)
	if (elem->GetRc().top>-1640) {
		EraseBlueShell(elem);
		break;
	}

	Physics::GetInstance()->DefenseW();

	//for (int i = 0; i < mBlueShellList.size(); i++) {
	//	if (mBlueShellList[i] == NULL) {
	//		mBlueShellList.erase(mBlueShellList.begin() + i);
	//		i--;
	//	}
	//}


}

void YetiAndPepe::StatusSwitch()
{
	switch (mStatus) {

	case Status1::leftIdle:
		mFrameY = 0;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 2) { mFrameX = 0; mStatus = Status1::Attack; }
		break;
	case Status1::Attack:
		mFrameY = 1;
		if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
		if (mFrameX > 8) { mFrameX = 0; mStatus = Status1::leftIdle; }
		break;
	}
}

void YetiAndPepe::EraseBlueShell(BlueShell* blueShellPtr)
{

	for (int i = 0; i < mBlueShellList.size(); i++) {
		if (mBlueShellList[i] == blueShellPtr) {
			SafeDelete(mBlueShellList[i]);
			mBlueShellList.erase(mBlueShellList.begin() + i);
			i--;
		}
	}

}
