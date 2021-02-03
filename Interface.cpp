#include "main.h"
#include "Physics.h"
#include "Player.h"
#include "Image.h"
#include "Interface.h"


void Main::InterfaceRender(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);

	//미니맵 Minimap
	if (mToggeleMiniMap) { 
		wstring Alert = L"Mini Map"; 
		SetTextColor(hdc, RGB(0,0,0));
		HFONT newFont = CreateFontW(20, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Algerian"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		TextOut(hdc, 1168, 0, Alert.c_str(), Alert.size());
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);

		//mBkBuff->ScaleRender(hdc, 1170, 20, 80, 130); 
		StretchBlt(hdc, 1170, 20, 80,130, mBkBuff->GetHDC(), 0, 0, 1280,720, SRCCOPY); //미니맵에 인터페이스는 안보이게
	}

	//데미지 인터페이스
	Interface::GetInstance()->DamageEffectRender(hdc, Physics::GetInstance()->GethitBox().left, Physics::GetInstance()->GethitBox().top,
		Physics::GetInstance()->GethitBox().right - Physics::GetInstance()->GethitBox().left);

	//스킬창 인터페이스 Skill interface toggle
	Interface::GetInstance()->Render(hdc);
	
}

void Interface::Update()
{
	if (mPlayer->GetY() < -720) mLevel = 2;
	else mLevel = 1;
	if (mPlayer->GetY() < -720-1440) mLevel = 3;

	if (Input::GetInstance()->GetKeyD('S')) { mToggleInterface = !mToggleInterface; }

	if (mPlayer->GetSkillQTime() > -200) {
		if (mAlphaQ > 0.9f) mAlphaQ = 0.3f;
		mAlphaQ += 0.01f;

	}
	else mAlphaQ = 0.7f;

	if (mPlayer->GetSkillWTime() > -500 and mPlayer->GetSkillWTime()<300) {
		if (mAlphaW > 0.9f) mAlphaW = 0.3f;
		mAlphaW += 0.01f;

	}
	else mAlphaW = 0.7f;

	if (Input::GetInstance()->GetKey('E') and mPlayer->GetMP()>0) {
		if (mAlphaE > 0.9f) mAlphaE = 0.3f;
		mAlphaE += 0.01f;
	}
	else mAlphaE = 0.7f;

	if (mPlayer->GetIsDead()) {
		if (mAlphaR > 0.9f) mAlphaR = 0.3f;
		mAlphaR += 0.01f;
	}
	else mAlphaR = 0.7f;
}

void Interface::Render(HDC hdc)
{
	if (mToggleInterface) { //스킬창 인터페이스 렌더 Skill UI render
		mImage->AlphaFrameRender(hdc, 30, 50, 0, 0,  0.7f);
		mImage->AlphaFrameRender(hdc, 30, 140, 1, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 230, 2, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 320, 3, 0, 0.7f);
	}
	if (mPlayer->GetSkillQTime() > -200) { //스킬 Q 쿨다운 체커 Skill Q cooldown checker
		mImage->AlphaScaleFrameRender(hdc, 1180, 230, 0, 0, 60,60,mAlphaQ);

		wstring Cooldown = to_wstring((300 + mPlayer->GetSkillQTime()) / 100);
		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(60, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		RECT rc = RectMake(1180, 230, 60, 60);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &rc, DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);

	}

	if (mPlayer->GetSkillWTime() > 0 and mPlayer->GetSkillWTime() < 300) { //스킬 W 활성 체커 Skill W activation checker

		mImage->AlphaScaleFrameRender(hdc, 1030, 10, 1, 0, 50, 50, mAlphaW);

		wstring Cooldown = to_wstring((mPlayer->GetSkillWTime()+100)/100);
		SetTextColor(hdc, RGB(0, 0, 255));
		HFONT newFont = CreateFontW(50, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		RECT rc = RectMake(1030, 10, 50, 50);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &rc, DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	if (mPlayer->GetSkillWTime() > -500 and mPlayer->GetSkillWTime() < 0) { //스킬 W 쿨다운 체커 Skill W cooldown checker
		mImage->AlphaScaleFrameRender(hdc, 1180, 300, 1, 0, 60, 60, mAlphaW);

		wstring Cooldown = to_wstring((600 + mPlayer->GetSkillWTime()) / 100);
		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(60, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		RECT rc = RectMake(1180, 300, 60, 60);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &rc, DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	if (Input::GetInstance()->GetKey('E') and mPlayer->GetMP()>0) { //스킬 E 활성 체커 Skill E activation checker

		mImage->AlphaScaleFrameRender(hdc, 1080, 10, 2, 0, 50,50, mAlphaE);
	}

	if (mPlayer->GetIsDead()) { //스킬 R 활성 체커 Skill R activation checker

		mImage->AlphaFrameRender(hdc, WINSIZEX/2-35, WINSIZEY/2-35, 3, 0, mAlphaR);
	}

	mInterface->Render(hdc, 0, 720); //인터페이스 창 출력
	if (true) {

		SetTextColor(hdc, RGB(255, 255, 255));
		HFONT newFont = CreateFontW(0, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
	
		//체력
		float hp = (float)mPlayer->GetHP() / 1000;
		mHpBar->ScaleRender(hdc, 404, 717, hp * 226, 40);

		wstring hpint =to_wstring(mPlayer->GetHP()) + L" / 1000";
		RECT rc = RectMake(410, 723, 220, 20);
		DrawText(hdc, hpint.c_str(), hpint.length(), &rc, DT_LEFT);

		//마나
		float mp = (float)mPlayer->GetMP() / 1000;
		mMpBar->ScaleRender(hdc, 675, 720, mp * 226, 40);

		wstring mpint = to_wstring(mPlayer->GetMP()) + L" / 1000";
		RECT rc1 = RectMake(680, 723, 220, 20);
		DrawText(hdc, mpint.c_str(), mpint.length(), &rc1, DT_LEFT);

		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
		
		wstring level = to_wstring(mLevel); //레벨 인터페이스 렌더 Level UI render
		SetTextColor(hdc, RGB(179,153,0));
		newFont = CreateFontW(20, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		oldFont = (HFONT)SelectObject(hdc, newFont);
		RECT levelRc = RectMake(70, 730, 20, 20);
		DrawTextW(hdc, level.c_str(), level.size(), &levelRc, DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}
	
	//플레이어 데미지 이펙트
	int damage = tempHP - mPlayer->GetHP();
	if (damage > 0) { mHpDamageEffectOn = true; mDamage = damage; }
	PlayerDamageEffectRender(hdc, mDamage);

	tempHP = mPlayer->GetHP();


}

void Interface::DamageEffectRender(HDC hdc, float x, float y, float W)
{
	if (mDamageEffectOn) {

		mDamageEffectCount++;
		float Alpha = (float)(51-mDamageEffectCount)/51;
		float Width = W * 0.9;
		float Height = W * 0.45;

		if (Width < 80) { Width = 80, Height = 40; }

		mMiss->AlphaScaleFrameRender(hdc, x, y - Camera::GetInstance()->GetY(),0, mRandFrameY, Width, Height, Alpha);

		if (mDamageEffectCount > 50) {
			mDamageEffectCount = 0;
			mRandFrameY = Random::GetInstance()->RandInt(3);
			mDamageEffectOn = false;
		}
	}
}

void Interface::PlayerDamageEffectRender(HDC hdc, int damage)
{
	//낙사 주의 Fall death alert
	if (Physics::GetInstance()->GetG() > 25) {
		float alpha = Physics::GetInstance()->GetG();
		mCaution->AlphaScaleRender(hdc, 500, 250, 300, 300, alpha/75);
	}

	//데미지 이펙트 렌더 Damage Effect Render
	if (mHpDamageEffectOn) {

		mHpDamageEffectCount++;

		int x = mPlayer->GetX()-10;
		int y = mPlayer->GetY() -30 - Camera::GetInstance()->GetY();

		int hundreds = damage / 100;
		int tens = (damage-hundreds*100) / 10;
		int ones = damage % 10;

		float alpha = (51.f - (float)mHpDamageEffectCount) / 51;

		if (damage > 199) {
			mNumbers->AlphaScaleFrameRender(hdc, x, y, hundreds, 1, 36, 37, alpha);
			mNumbers->AlphaScaleFrameRender(hdc, x+33, y, tens, 1, 36, 37, alpha);
			mNumbers->AlphaScaleFrameRender(hdc, x+60,y, ones, 1, 36,37, alpha);
		}
		else {
			if (damage > 99) mNumbers->AlphaScaleFrameRender(hdc, x, y, hundreds, 0, 36, 37, alpha);
			if (damage > 9)  mNumbers->AlphaScaleFrameRender(hdc, x + 33, y, tens, 0, 36, 37, alpha);
			mNumbers->AlphaScaleFrameRender(hdc, x + 60, y, ones, 0, 36, 37, alpha);
		}
	}

	if (mHpDamageEffectCount > 50) { mHpDamageEffectCount = 0; mHpDamageEffectOn = false; }
}
