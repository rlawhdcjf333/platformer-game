#include "pch.h"
#include "Player.h"
#include "Skill.h"
#include "Aim.h"
#include "RedShell.h"
#include "Image.h"
#include "Physics.h"

void Player::istheSkill() {

	//Q ��ٿ� skill Q cooldown 
	SkillQTime--;
	if (SkillQTime < -200) SkillQTime = -200; //cooldown 2sec

	// Q ���� �� �ߵ� skill Q lockon and activation
	if (mMP >= 50) {
		if (Input::GetInstance()->GetKey('Q') and SkillQTime == -200) {

			Aim::GetInstance()->On();
			SkillQ = true;
		}
		if (SkillQ == true and mSkill->GetQPower() < 50) mSkill->SetQPower(mSkill->GetQPower() + 0.8f);
		if (Input::GetInstance()->GetKeyU('Q') and SkillQTime == -200) {
			mMP -= 50;
			float Angle = Aim::GetInstance()->GetAimAngle();
			if (0.5 * PI < Angle and Angle < 1.5 * PI)mStatus = Status::leftThrow;
			else mStatus = Status::rightThrow;

			RedShell* mRedShell = new RedShell();
			mRedShell->SetXY(mX + 40, mY + 45);
			mRedShell->Init(mSkill->GetQPower(), Angle);
			mSkill->AddRedShellQ(mRedShell);
			SkillQ = false;
			SkillQTime = 0;
			mSkill->SetQPower(0);
			Aim::GetInstance()->Off();
		}
	}
	//W ��ٿ� ����
	SkillWTime--;
	if (SkillWTime < -500) SkillWTime = -500;
	// W �ߵ� skill W activation
	if (mMP >= 200) {
		if (Input::GetInstance()->GetKeyD('W') and SkillW == false) {
			mMP -= 200;
			RedShell* mRedShell = new RedShell();
			for (int i = 0; i < 10; i++) {
				mRedShell = new RedShell();
				mRedShell->SetXY(mX + 40 + 150 * cosf(0.2 * i * PI), mY + 45 - 150 * sinf(0.2 * i * PI));
				mRedShell->Init(0, 0);
				mSkill->AddRedShellW(mRedShell);
			}
			SkillW = true;
			SkillWTime = 300; // effect remains for 3 sec
		}
	}
	//��� ����ü ������Ʈ Projectile(all if any;) Update
	for (RedShell*& elem : mSkill->GetRedShellListQ()) {
		if (elem != NULL) elem->Update();
	}
	for (RedShell*& elem : mSkill->GetRedShellListW()) {
		if (elem != NULL) {
			float Angle = Math::GetAngle(mX+40, mY+45, elem->GetX() + 13, elem->GetY() + 13);
			elem->SetXY(mX+40 + 150*cosf(Angle-0.07*PI), mY + 45 - 150* sinf(Angle - 0.07 * PI));
			elem->Move();
		}
	}

	//ȭ�� �� Q ����ü ���� release Q projectiles under the bottomline
	for (RedShell*& elem : mSkill->GetRedShellListQ()) {
		if (elem != NULL) {
			if (elem->GetRc().top > WINSIZEY) { 
				mSkill->EraseRedShellQ(elem);
			}
		}
	}

	// ���� ������ Q ����ü ���� @ Singleton Physics, release the Q projectile hitting an enemy
	Physics::GetInstance()->EraseQ(); 

	// W ���ӽð� ���� �� ��ٿ� skill W ending and cooldown
	if (SkillWTime == 0) {
		for (RedShell*& elem : mSkill->GetRedShellListW()) {
			mSkill->EraseRedShellW(elem);
		}
	}
	if (SkillWTime == -500) SkillW = false; //cooldown 5 sec
}

void Skill::EraseRedShellQ(RedShell* redShellPtr)
{
	for (int i = 0; i < mRedShellListQ.size(); i++) {
		if (mRedShellListQ[i] == redShellPtr) {
			SafeDelete(mRedShellListQ[i]);
			mRedShellListQ.erase(mRedShellListQ.begin() + i);
			i--;
		}
	}
}

void Skill::EraseRedShellW(RedShell* redShellPtr)
{
	for (int i = 0; i < mRedShellListW.size(); i++) {
		if (mRedShellListW[i] == redShellPtr) {
			SafeDelete(mRedShellListW[i]);
			mRedShellListW.erase(mRedShellListW.begin() + i);
			i--;
		}
	}
}

void Skill::Render(HDC hdc)
{
	//Q ���� Skill Q
	for (RedShell* elem : mRedShellListQ) {
		if (elem != NULL) elem->Render(hdc);
	}

	//W ���� Skill W
	for (RedShell* elem : mRedShellListW) {
		if (elem != NULL) elem->Render(hdc);
	}

	//E ���� Skill E
	if (Input::GetInstance()->GetKey('E') and mPlayer->GetMP()>0)
		mImage->AlphaRender(hdc, mPlayer->GetX() + 15 -Camera::GetInstance()->GetX(), 
			mPlayer->GetY() - 50 - Camera::GetInstance()->GetY(), 0.7f);

}

void Skill::Release()
{
	for (RedShell*& elem : mRedShellListQ) {
		SafeDelete(elem)
	}

	for (RedShell*& elem : mRedShellListW) {
		SafeDelete(elem)
	}

}
