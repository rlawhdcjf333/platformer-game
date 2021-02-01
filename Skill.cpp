#include "pch.h"
#include "Player.h"
#include "Skill.h"
#include "Aim.h"
#include "RedShell.h"
#include "Physics.h"

void Player::istheSkill() {

	SkillQTime--;
	if (SkillQTime < -200) SkillQTime = -200;
	if (SkillQ == true and mSkill->GetQPower()<50) mSkill->SetQPower(mSkill->GetQPower() + 0.8f);

	
	if (Input::GetInstance()->GetKey('Q') and SkillQTime==-200) { //������ ������ ���� ��� ��ٿ� 2��

		Aim::GetInstance()->On();
		SkillQ = true;
	}
	if (Input::GetInstance()->GetKeyU('Q') and SkillQTime == -200) {// ������ ������ �ߵ�

		float Angle = Aim::GetInstance()->GetAimAngle();
		if (0.5*PI<Angle and Angle<1.5*PI)mStatus = Status::leftThrow;
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


	SkillWTime--;
	if (SkillWTime < -500) SkillWTime = -500;
	if (Input::GetInstance()->GetKeyD('W') and SkillW==false) {// ������ ��� �ߵ�
		RedShell* mRedShell = new RedShell();
		for (int i = 0; i < 25; i++) { //��� �ȹ� ��ġ �ʱ�ȭ
			mRedShell = new RedShell();
			mRedShell->SetXY(mX + 40 + 150 * cosf(0.08 * i * PI), mY + 45 - 150 * sinf(0.08 * i * PI));
			mRedShell->Init(0, 0);
			mSkill->AddRedShellW(mRedShell);
		}
		SkillW = true;
		SkillWTime = 300; //���� 3��
	}

	//���� (������) ������Ʈ
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

	//���� Ʈ����
	for (RedShell*& elem : mSkill->GetRedShellListQ()) {
		if (elem != NULL) {
			if (elem->GetRc().top > WINSIZEY) { //â��(�Ʒ�)���� ������ ��
				mSkill->EraseRedShellQ(elem);
			}
		}
	}

	Physics::GetInstance()->EraseQ(); // ���� ������ ��, Physics �̱���

	if (SkillWTime == 0) {
		for (RedShell*& elem : mSkill->GetRedShellListW()) {
			mSkill->EraseRedShellW(elem);
		}
	}
	if (SkillWTime == -500) SkillW = false; //W ��ٿ� 5��
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
	for (RedShell* elem : mRedShellListQ) {
		if (elem != NULL) elem->Render(hdc);
	}

	for (RedShell* elem : mRedShellListW) {
		if (elem != NULL) elem->Render(hdc);
	}

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
