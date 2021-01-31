#include "pch.h"
#include "Physics.h"
#include "Player.h"
#include "Projectile.h"
#include "Map.h"
#include "Enemy.h"
#include "GreenShell.h"
#include "BlueShell.h"
#include "WitchCat.h"
#include "YetiAndPepe.h"
#include "MossSnail.h"
#include "Fanzy.h"
#include "Launcher.h"

Physics::Physics()
{
	mGravity = 0.58f;
}


void Physics::PhysicsUpdate()
{
	mGravity += 0.58f;
	mPlayer->SetY(mPlayer->GetY() + mGravity);


}

void Physics::IsonthePlatform() {

	mPlayer->SetonthePlatform(false);
	mPlayer->SetontheRope(false);
	mPlayer->SetontheLadder(false);

	if (mPlayer->GetStatus() != Status::laddering and mPlayer->GetStatus() !=Status::rope) {
		//바닥 판정
		for (RECT elem : mMapList[0]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetY(elem.top - 93);
					break;
				}
			}
		}

		//2단계 미끌바닥 판정
		for (RECT elem : mMapList[2]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetX(mPlayer->GetX() + 0.07); //0.07 만큼 오른쪽으로 계속 미끄러진다
					mPlayer->SetY(elem.top - 93);
					break;
				}
			}
		}

	}

	//투명 바닥 판정
	Fanzy* fanzyPtr = (Fanzy*)mEnemyList[4]; //투명냥이 팬지 다운 캐스팅
	if (fanzyPtr->GetInvisibility() == true) { //비록 변수로 읽으면 투명함 트루(...왜그랬지)이지만 프로그래밍상 반대의 의미

		for (RECT elem : fanzyPtr->GetRcList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetY(elem.top - 91); //작은 픽셀 차 (이미지 렌더)때문에 얘는 2픽셀 덜 빼준다...
					break;
				}
			}
		}

	}

	//로프 판정
	for (RECT elem : {mMapList[1]->GetMapList()[0], mMapList[1]->GetMapList()[1]}) {
		for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
			if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
				mPlayer->SetontheRope(true);
				if (mPlayer->GetStatus() == Status::rope) {
					mGravity = -0.58f;
					mPlayer->SetVec(0);
					mPlayer->SetX(elem.left -38);
				}
				break;
			}
		}
	}

	//사다리 판정
	for (RECT elem : {mMapList[1]->GetMapList()[2]}) {
		for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
			if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
				mPlayer->SetontheLadder(true);
				if (mPlayer->GetStatus() == Status::laddering) {
					mGravity = -0.58f;
					mPlayer->SetVec(0);
					mPlayer->SetX(elem.left-10);
				}

				break;
			}
		}
	}

	//1단계 무빙쉘 판정
	RECT temp{};
	RECT hitBox = { mPlayer->GetRc().left + 22, mPlayer->GetRc().top, mPlayer->GetRc().left + 55,mPlayer->GetRc().bottom };
	for (RECT elem : mMapList[3]->GetMapList()) {
		if (IntersectRect(&temp, &elem, &hitBox)) {
			mPlayer->SetonthePlatform(false);
			mGravity = -0.58f;
			mPlayer->SetVec(15);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			if (mPlayer->GetX() + 40 > (temp.right + temp.left) / 2) 
			{ mPlayer->SetAngle(0.2 * PI);  mPlayer->SetStatus(Status::leftJump);}
			else 
			{ mPlayer->SetAngle(0.8 * PI); mPlayer->SetStatus(Status::rightJump);}
			break;
		}
	}

	//깨시 판정
	for (RECT elem : mMapList[4]->GetMapList()) {
		for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
			if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
				mPlayer->SetonthePlatform(false);
				mPlayer->SetStatus(Status::leftJump);
				mGravity = -0.58f;
				mPlayer->SetVec(20);
				mPlayer->SetAngle(PI * 0.4);
				break;
			}
		}
	}

}

void Physics::SetMap(vector<Map*> mapPtrList)
{
	for (int i = 0; i < mapPtrList.size(); i++) {

		mMapList.push_back(mapPtrList[i]);
	}

}

void Physics::SetEnemy(vector<Enemy*> enemyPtrList) {
	
	for (int i = 0; i < enemyPtrList.size(); i++) {

		mEnemyList.push_back(enemyPtrList[i]);
	}

}

void Physics::IstheHit()
{
	RECT temp{};
	RECT hitBox = { mPlayer->GetRc().left + 22, mPlayer->GetRc().top, mPlayer->GetRc().left + 55,mPlayer->GetRc().bottom };

	WitchCat* witchCatPtr = (WitchCat*)mEnemyList[0]; //왼쪽 냥이 다운 캐스팅... 몹마다 던지는 쉘이 다르므로 다운캐스팅이 필요
	for (GreenShell* elem : witchCatPtr->GetGreenShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			mGravity = -0.58f;
			mPlayer->SetVec(10);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(3);
			mPlayer->SetAngle(PI * 0.3);
			mPlayer->SetStatus(Status::leftJump);
			break;
		}
	}

	witchCatPtr = (WitchCat*)mEnemyList[1];  //오른쪽 냥이 다운 캐스팅
	for (GreenShell* elem : witchCatPtr->GetGreenShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			mGravity = -0.58f;
			mPlayer->SetVec(10);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(3);
			mPlayer->SetAngle(PI * 0.7);
			mPlayer->SetStatus(Status::rightJump);
			break;
		}
	}

	YetiAndPepe* yetiAndPepePtr = (YetiAndPepe*)mEnemyList[2]; //예티와페페 다운 캐스팅
	for (BlueShell* elem : yetiAndPepePtr->GetBlueShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			mGravity = -0.58f;
			mPlayer->SetVec(20);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			mPlayer->SetAngle(PI * 1.2);
			mPlayer->SetStatus(Status::rightJump);
			break;
		}

	}

	MossSnail* mossSnailPtr = (MossSnail*)mEnemyList[3];
	for (RcAndRange& elem : mossSnailPtr->GetSnail()) { //struct 비싸니까 싸게 가져오자... 
		RECT hitter = elem.rc;
		if(IntersectRect(&temp, &hitter, &hitBox)) {
			mGravity = -0.58f;
			mPlayer->SetVec(15);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			if (mPlayer->GetX() + 40 > (temp.right + temp.left) / 2) 
			{ mPlayer->SetAngle(0.3 * PI);  mPlayer->SetStatus(Status::leftJump);}
			else 
			{ mPlayer->SetAngle(0.7 * PI); mPlayer->SetStatus(Status::rightJump);}
			break;
		}

	}

	Launcher* launcherPtr = (Launcher*)mMapList[5]; //STL map으로 구현한 런쳐 다운캐스팅
	for (int i = 1; i < 5; i++) {
		if (launcherPtr->GetLauncherList().find(to_string(i))->second != NULL) {
			RECT hitter = launcherPtr->GetLauncherList().find(to_string(i))->second->GetRc();
			if (IntersectRect(&temp, &hitter, &hitBox)) {
				mGravity = -0.58f;
				mPlayer->SetVec(20);
				mPlayer->SetAngle(PI * 0.1);
				mPlayer->SetStatus(Status::leftJump);
				break;
			}
		}
	}
	


}

