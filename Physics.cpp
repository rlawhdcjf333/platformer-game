#include "pch.h"
#include "Physics.h"
#include "Player.h"
#include "Skill.h"
#include "Map.h"
#include "Enemy.h"
#include "GreenShell.h"
#include "BlueShell.h"
#include "RedShell.h"
#include "WitchCat.h"
#include "YetiAndPepe.h"
#include "MossSnail.h"
#include "Fanzy.h"
#include "Launcher.h"
#include "Interface.h"

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
		
		//바닥 판정 Fixed plats 
		for (RECT elem : mMapList[0]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) { //발 밑 가로 길이 33 픽셀
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) { //이미지 렉트 바닥으로부터 2픽셀 위
					mDamage = mGravity; //충돌 순간 중력값 == 낙하 피해량
					mPlayer->SetonthePlatform(true); //플레이어 상태 갱신
					mGravity = -0.58f; //중력 초기화
					mPlayer->SetY(elem.top - 93); //플레이어 위치 보정
					break;
				}
			}
		}

		//2단계 미끌바닥 판정 Level 2 slippery plats
		for (RECT elem : mMapList[2]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mDamage = mGravity;
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetX(mPlayer->GetX() + 0.07); //0.07 만큼 오른쪽으로 계속 미끄러진다
					mPlayer->SetY(elem.top - 93);
					break;
				}
			}
		}

		if (mDamage > 25) { mGravity = 0; mPlayer->SetHP(mPlayer->GetHP() - mDamage * 7); } //낙하 피해량 25초과에서 실제 낙하 데미지(데미지 계수 7) 구현
	}

	//투명 바닥 판정 Invisible plats
	Fanzy* fanzyPtr = (Fanzy*)mEnemyList[4]; //투명냥이 팬지 다운 캐스팅
	if (fanzyPtr->GetInvisibility() == true) { 
		for (RECT elem : fanzyPtr->GetRcList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetY(elem.top - 91); 
					break;
				}
			}
		}

	}

	//로프 판정 Ropes
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

	//사다리 판정 Ladders
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

	//1단계 무빙쉘 판정 Moving Shells
	RECT temp{};
	RECT hitBox = { mPlayer->GetRc().left + 22, mPlayer->GetRc().top, mPlayer->GetRc().left + 55,mPlayer->GetRc().bottom };
	for (RECT elem : mMapList[3]->GetMapList()) {
		if (IntersectRect(&temp, &elem, &hitBox)) {
			mPlayer->SetonthePlatform(false);
			mPlayer->SetVec(15);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			if (mPlayer->GetX() + 40 > ((float)temp.right + (float)temp.left) / 2) 
			{ mPlayer->SetAngle(0.2 * PI);  mPlayer->SetStatus(Status::leftJump);}
			else 
			{ mPlayer->SetAngle(0.8 * PI); mPlayer->SetStatus(Status::rightJump);}
			break;
		}
	}

	//깨시 판정 Thorns
	for (RECT elem : mMapList[4]->GetMapList()) {
		for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
			if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
				mPlayer->SetonthePlatform(false);
				mPlayer->SetStatus(Status::leftJump);
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

RECT Physics::GethitBox()
{
	return mhitBox;
}

void Physics::IstheHit()
{
	RECT temp{};
	RECT hitBox = { mPlayer->GetRc().left + 22, mPlayer->GetRc().top, mPlayer->GetRc().left + 55,mPlayer->GetRc().bottom };

	WitchCat* witchCatPtr = (WitchCat*)mEnemyList[0]; //왼쪽 냥이 다운 캐스팅... 몹마다 던지는 쉘이 다르므로 다운캐스팅이 필요
	for (GreenShell* elem : witchCatPtr->GetGreenShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			mPlayer->SetVec(10);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(3); //엎드린 상태에서 맞으면 덜 밀리게
			mPlayer->SetAngle(PI * 0.3);
			mPlayer->SetStatus(Status::leftJump);
			break;
		}
	}

	witchCatPtr = (WitchCat*)mEnemyList[1];  //오른쪽 냥이 다운 캐스팅
	for (GreenShell* elem : witchCatPtr->GetGreenShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
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
			mPlayer->SetonthePlatform(false);
			mPlayer->SetVec(15);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			mPlayer->SetAngle(PI * 0.95);
			mPlayer->SetStatus(Status::rightJump);
			break;
		}

	}

	MossSnail* mossSnailPtr = (MossSnail*)mEnemyList[3];
	for (RcAndRange& elem : mossSnailPtr->GetSnail()) { //struct 비싸니까 싸게 가져오자... 
		RECT hitter = elem.rc;
		if(IntersectRect(&temp, &hitter, &hitBox)) {
			mPlayer->SetVec(15);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(5);
			if (mPlayer->GetX() + 40 > ((float)temp.right + (float)temp.left) / 2) 
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
				mPlayer->SetVec(20);
				mPlayer->SetAngle(PI * 0.1);
				mPlayer->SetStatus(Status::leftJump);
				break;
			}
		}
	}
	


}

void Physics::WitchCatHit()
{

	RECT temp{};
	RECT hitter{};
	RECT hitBox{};
	
	for (Enemy* elem : { mEnemyList[0], mEnemyList[1]}) {
		for (RedShell* elem1 : mPlayer->GetSkill()->GetRedShellListQ()) {
			hitBox = elem->GetRc();
			hitter = elem1->GetRc();
			if (IntersectRect(&temp, &hitter, &hitBox)) {
				
				WitchCat* witchCatL = (WitchCat*)mEnemyList[0]; //좌냥이 다운캐스팅 LCat downcasting from enemy
				WitchCat* witchCatR = (WitchCat*)mEnemyList[1]; //우냥이 다운캐스팅 RCat downcasting from enemy

				switch (elem == mEnemyList[0]) {

				case true:
					witchCatL->SetStatus(Status0::rightHit); //좌냥이 피격모션 활성 Hit motion activation
					mPlayer->GetSkill()->EraseRedShellQ(elem1); //투사체 삭제 erase projectile
					break;

				case false:
					witchCatR->SetStatus(Status0::leftHit); //우냥이 피격모션 활성
					mPlayer->GetSkill()->EraseRedShellQ(elem1); // 투사체 삭제
					break;
				}
				
			}
		}
	}

	
}

void Physics::DefenseW()
{
	if (mPlayer->GetSkill()->GetRedShellListW().size() > 0) { //W 스킬의 달팽이 껍질이 하나라도 존재할 때만
		RECT temp{};
		RECT defender{};
		RECT defendee{};

		YetiAndPepe* yetiAndPepePtr = (YetiAndPepe*)mEnemyList[2]; //지금 드는 생각인데 Enemy관리를 map으로 했으면 좋았을 것 같다;;;
		for (BlueShell* elem : yetiAndPepePtr->GetBlueShellList()) {
			defendee = elem->GetRc();
			defender = RectMake(mPlayer->GetX()-80, mPlayer->GetY()-80, 240,255);
			if (IntersectRect(&temp, &defender, &defendee)) {

				yetiAndPepePtr->EraseBlueShell(elem);

			}
		}
	}
}


void Physics::EraseQ()
{
	RECT temp{};
	RECT hitter{};
	RECT hitBox{};


	//예티와페페 피격 YetiAndPepe hit 
		hitBox = mEnemyList[2]->GetRc();
	for (RedShell* elem1 : mPlayer->GetSkill()->GetRedShellListQ()) {
		hitter = elem1->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			
			mPlayer->GetSkill()->EraseRedShellQ(elem1);
			mhitBox = hitBox;
			Interface::GetInstance()->SetDamageEffect(true); //데미지 효과 렌더 요청 @ Singleton Interface, Damage effect rendering request
		}
	}

	//이끼달팽이 피격 MossSnail hit
	MossSnail* mossSnailPtr = (MossSnail*)mEnemyList[3]; //에너미 포인터를 이끼 달팽이 포인터로 다운캐스팅
	for (RedShell* elem1 : mPlayer->GetSkill()->GetRedShellListQ()) {
		hitter = elem1->GetRc();
		for (RcAndRange& elem : mossSnailPtr->GetSnail()) {
			hitBox = elem.rc;
			if (IntersectRect(&temp, &hitter, &hitBox)) {

				mPlayer->GetSkill()->EraseRedShellQ(elem1);
				mhitBox = hitBox;
				Interface::GetInstance()->SetDamageEffect(true); 
			}

		}
	}
}