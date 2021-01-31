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
		//�ٴ� ����
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

		//2�ܰ� �̲��ٴ� ����
		for (RECT elem : mMapList[2]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetX(mPlayer->GetX() + 0.07); //0.07 ��ŭ ���������� ��� �̲�������
					mPlayer->SetY(elem.top - 93);
					break;
				}
			}
		}

	}

	//���� �ٴ� ����
	Fanzy* fanzyPtr = (Fanzy*)mEnemyList[4]; //�������� ���� �ٿ� ĳ����
	if (fanzyPtr->GetInvisibility() == true) { //��� ������ ������ ������ Ʈ��(...�ֱ׷���)������ ���α׷��ֻ� �ݴ��� �ǹ�

		for (RECT elem : fanzyPtr->GetRcList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetY(elem.top - 91); //���� �ȼ� �� (�̹��� ����)������ ��� 2�ȼ� �� ���ش�...
					break;
				}
			}
		}

	}

	//���� ����
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

	//��ٸ� ����
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

	//1�ܰ� ������ ����
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

	//���� ����
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

	WitchCat* witchCatPtr = (WitchCat*)mEnemyList[0]; //���� ���� �ٿ� ĳ����... ������ ������ ���� �ٸ��Ƿ� �ٿ�ĳ������ �ʿ�
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

	witchCatPtr = (WitchCat*)mEnemyList[1];  //������ ���� �ٿ� ĳ����
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

	YetiAndPepe* yetiAndPepePtr = (YetiAndPepe*)mEnemyList[2]; //��Ƽ������ �ٿ� ĳ����
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
	for (RcAndRange& elem : mossSnailPtr->GetSnail()) { //struct ��δϱ� �ΰ� ��������... 
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

	Launcher* launcherPtr = (Launcher*)mMapList[5]; //STL map���� ������ ���� �ٿ�ĳ����
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
