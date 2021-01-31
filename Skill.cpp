#include "pch.h"
#include "Status.h"
#include "Player.h"
#include "Skill.h"
#include "Aim.h"
#include "RedShell.h"

void Player::istheSkill() {

	SkillQTime--;
	if (SkillQTime < -200) SkillQTime = -200;
	if (SkillQ == true and mSkill->GetQPower()<50) mSkill->SetQPower(mSkill->GetQPower() + 0.5f);

	if (Input::GetInstance()->GetKey('Q') and SkillQTime==-200) { //달팽이 던지기 조준 토글 // 쿨다운 2초

		Aim::GetInstance()->On();
		SkillQ = true;
	}
	if (Input::GetInstance()->GetKeyU('Q') and SkillQTime == -200) {// 달팽이 던지기 발동
		RedShell* mRedShell = new RedShell();
		mRedShell->SetXY(mX + 40, mY + 45);
		mRedShell->Init(mSkill->GetQPower(), Math::GetAngle(mX + 40, mY + 45, Aim::GetInstance()->GetX(), Aim::GetInstance()->GetY()));
		mSkill->AddRedShellQ(mRedShell);
		SkillQ = false;
		SkillQTime = 0;
		mSkill->SetQPower(0);
		Aim::GetInstance()->Off();
	}


	SkillWTime--;
	if (SkillWTime < -500) SkillWTime = -500;
	if (Input::GetInstance()->GetKeyD('W') and SkillW==false) {// 달팽이 방어 발동
		RedShell* mRedShell = new RedShell();
		mRedShell->SetXY(mX + 40, mY + 45 - 100);
		mRedShell->Init(0, 0);
		mSkill->AddRedShellW(mRedShell);
		SkillW = true;
		SkillWTime = 500; //지속 5초
	}

	//각각 (있으면) 업데이트
	for (RedShell*& elem : mSkill->GetRedShellListQ()) {
		if (elem != NULL) elem->Update();
	}
	
	for (RedShell*& elem : mSkill->GetRedShellListW()) {
		if (elem != NULL) {
			float Angle = Math::GetAngle(mX+40, mY+45, elem->GetX() + 13, elem->GetY() + 13);
			elem->SetXY(mX+40 + 150*cosf(Angle-0.1*PI), mY + 45 - 150 * sinf(Angle - 0.1 * PI));
			elem->Move();
		}
	}

	//삭제 트리거
	for (RedShell*& elem : mSkill->GetRedShellListQ()) {
		if (elem != NULL) {
			if (elem->GetRc().top > WINSIZEY) { //창밖(아래)으로 나가면 컷, 몹 피격은 physics가 한다
				mSkill->EraseRedShellQ(elem);
			}
		}
	}

	if (SkillWTime == 0) {
		for (RedShell*& elem : mSkill->GetRedShellListW()) {
			mSkill->EraseRedShellW(elem);
		}
	}
	if (SkillWTime == -500) SkillW = false; //W 쿨다운 5초
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
