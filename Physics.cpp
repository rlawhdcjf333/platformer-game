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
		
		//�ٴ� ���� Fixed plats 
		for (RECT elem : mMapList[0]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) { //�� �� ���� ���� 33 �ȼ�
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) { //�̹��� ��Ʈ �ٴ����κ��� 2�ȼ� ��
					mDamage = mGravity; //�浹 ���� �߷°� == ���� ���ط�
					mPlayer->SetonthePlatform(true); //�÷��̾� ���� ����
					mGravity = -0.58f; //�߷� �ʱ�ȭ
					mPlayer->SetY(elem.top - 93); //�÷��̾� ��ġ ����
					break;
				}
			}
		}

		//2�ܰ� �̲��ٴ� ���� Level 2 slippery plats
		for (RECT elem : mMapList[2]->GetMapList()) {
			for (int i = mPlayer->GetX() + 22; i < mPlayer->GetX() + 55; i++) {
				if (PtInRect(&elem, { i, mPlayer->GetRc().bottom - 2 })) {
					mDamage = mGravity;
					mPlayer->SetonthePlatform(true);
					mGravity = -0.58f;
					mPlayer->SetX(mPlayer->GetX() + 0.07); //0.07 ��ŭ ���������� ��� �̲�������
					mPlayer->SetY(elem.top - 93);
					break;
				}
			}
		}

		if (mDamage > 25) { mGravity = 0; mPlayer->SetHP(mPlayer->GetHP() - mDamage * 7); } //���� ���ط� 25�ʰ����� ���� ���� ������(������ ��� 7) ����
	}

	//���� �ٴ� ���� Invisible plats
	Fanzy* fanzyPtr = (Fanzy*)mEnemyList[4]; //������� ���� �ٿ� ĳ����
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

	//���� ���� Ropes
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

	//��ٸ� ���� Ladders
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

	//1�ܰ� ������ ���� Moving Shells
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

	//���� ���� Thorns
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

	WitchCat* witchCatPtr = (WitchCat*)mEnemyList[0]; //���� ���� �ٿ� ĳ����... ������ ������ ���� �ٸ��Ƿ� �ٿ�ĳ������ �ʿ�
	for (GreenShell* elem : witchCatPtr->GetGreenShellList()) {
		RECT hitter = elem->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			mPlayer->SetVec(10);
			if (mPlayer->GetStatus() == Status::rightDown or mPlayer->GetStatus() == Status::leftDown) mPlayer->SetVec(3); //���帰 ���¿��� ������ �� �и���
			mPlayer->SetAngle(PI * 0.3);
			mPlayer->SetStatus(Status::leftJump);
			break;
		}
	}

	witchCatPtr = (WitchCat*)mEnemyList[1];  //������ ���� �ٿ� ĳ����
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

	YetiAndPepe* yetiAndPepePtr = (YetiAndPepe*)mEnemyList[2]; //��Ƽ������ �ٿ� ĳ����
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
	for (RcAndRange& elem : mossSnailPtr->GetSnail()) { //struct ��δϱ� �ΰ� ��������... 
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

	Launcher* launcherPtr = (Launcher*)mMapList[5]; //STL map���� ������ ���� �ٿ�ĳ����
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
				
				WitchCat* witchCatL = (WitchCat*)mEnemyList[0]; //�³��� �ٿ�ĳ���� LCat downcasting from enemy
				WitchCat* witchCatR = (WitchCat*)mEnemyList[1]; //����� �ٿ�ĳ���� RCat downcasting from enemy

				switch (elem == mEnemyList[0]) {

				case true:
					witchCatL->SetStatus(Status0::rightHit); //�³��� �ǰݸ�� Ȱ�� Hit motion activation
					mPlayer->GetSkill()->EraseRedShellQ(elem1); //����ü ���� erase projectile
					break;

				case false:
					witchCatR->SetStatus(Status0::leftHit); //����� �ǰݸ�� Ȱ��
					mPlayer->GetSkill()->EraseRedShellQ(elem1); // ����ü ����
					break;
				}
				
			}
		}
	}

	
}

void Physics::DefenseW()
{
	if (mPlayer->GetSkill()->GetRedShellListW().size() > 0) { //W ��ų�� ������ ������ �ϳ��� ������ ����
		RECT temp{};
		RECT defender{};
		RECT defendee{};

		YetiAndPepe* yetiAndPepePtr = (YetiAndPepe*)mEnemyList[2]; //���� ��� �����ε� Enemy������ map���� ������ ������ �� ����;;;
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


	//��Ƽ������ �ǰ� YetiAndPepe hit 
		hitBox = mEnemyList[2]->GetRc();
	for (RedShell* elem1 : mPlayer->GetSkill()->GetRedShellListQ()) {
		hitter = elem1->GetRc();
		if (IntersectRect(&temp, &hitter, &hitBox)) {
			
			mPlayer->GetSkill()->EraseRedShellQ(elem1);
			mhitBox = hitBox;
			Interface::GetInstance()->SetDamageEffect(true); //������ ȿ�� ���� ��û @ Singleton Interface, Damage effect rendering request
		}
	}

	//�̳������� �ǰ� MossSnail hit
	MossSnail* mossSnailPtr = (MossSnail*)mEnemyList[3]; //���ʹ� �����͸� �̳� ������ �����ͷ� �ٿ�ĳ����
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