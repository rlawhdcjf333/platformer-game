#include "pch.h"
#include "Launcher.h"
#include "Camera.h"
#include "BlueShell.h"

void Launcher::Init()
{
	mY = -1200;
	mLaunchCount = 0;
	mFiringPower = 30;
	mLauncherList.insert(make_pair("1", nullptr));
	mLauncherList.insert(make_pair("2", nullptr));
	mLauncherList.insert(make_pair("3", nullptr));
	mLauncherList.insert(make_pair("4", nullptr));

}

void Launcher::Render(HDC hdc)
{
	map <string, BlueShell*>::iterator iter = mLauncherList.begin();
	for (;iter != mLauncherList.end(); iter++) {
		if(iter->second!=NULL)
		iter->second->Render(hdc);
	}
}

void Launcher::Release()
{
	map <string, BlueShell*>::iterator iter = mLauncherList.begin();
	for (;iter != mLauncherList.end(); iter++) {

		SafeDelete(iter->second)
	}
}

void Launcher::Update()
{
	map <string, BlueShell*>::iterator iter = mLauncherList.begin();

	mLaunchCount++;
	if (mLaunchCount > 450) mLaunchCount = 0;

	if (mLaunchCount == 75) { //1번 발사 2, 4 삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020);
		mBlueShell->Init(mFiringPower, 0.1*PI);
		mLauncherList.find("1")->second = mBlueShell;
		SafeDelete(mLauncherList.find("2")->second)
		SafeDelete(mLauncherList.find("4")->second)
	}
	if (mLaunchCount == 150) { // 2번 발사 1 삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 110);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("2")->second = mBlueShell;
		SafeDelete(mLauncherList.find("1")->second)
	}
	if (mLaunchCount == 225) { //3 발사 2 삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 106 - 110);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("3")->second = mBlueShell;
		SafeDelete(mLauncherList.find("2")->second)
	}
	if (mLaunchCount == 300) { //4발사 3삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 220 - 106);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("4")->second = mBlueShell;
		SafeDelete(mLauncherList.find("3")->second)
	}
	if (mLaunchCount == 375) { //1,3 발사 4삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("1")->second = mBlueShell;
		mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 106 - 110);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("3")->second = mBlueShell;
		SafeDelete(mLauncherList.find("4")->second)
	}
	if (mLaunchCount == 450) { //2,4 발사 1,3 삭제
		BlueShell* mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 110);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("2")->second = mBlueShell;
		mBlueShell = new BlueShell();
		mBlueShell->SetXY(40, -1020 - 220 - 106);
		mBlueShell->Init(mFiringPower, 0.1 * PI);
		mLauncherList.find("4")->second = mBlueShell;
		SafeDelete(mLauncherList.find("1")->second)
		SafeDelete(mLauncherList.find("3")->second)
	}

	for (;iter != mLauncherList.end(); iter++) {

		if (iter->second != NULL) iter->second->Update();
	}


}
