#include "main.h"
#include "Physics.h"
#include "Player.h"
#include "Image.h"
#include "Interface.h"


void Main::InterfaceRender(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);

	//�̴ϸ� Minimap
	if (mToggeleMiniMap) { 
		wstring Alert = L"Mini Map"; 
		SetTextColor(hdc, RGB(0,0,0));
		HFONT newFont = CreateFontW(20, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Algerian"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		TextOut(hdc, 1168, 0, Alert.c_str(), Alert.size());
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);

		mBkBuff->ScaleRender(hdc, 1170, 20, 80, 130); 
	}

	//���� ���� Fall death alert
	if (Physics::GetInstance()->GetG() > 25) {

		wstring Alert = L"����!"; //����
		if (Physics::GetInstance()->GetG() > 35) Alert = L"���!";//Ȯ�� ���

		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(100, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("����"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		TextOut(hdc, 50, 300, Alert.c_str(), Alert.size());
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	//������ �������̽�
	Interface::GetInstance()->DamageEffectRender(hdc, Physics::GetInstance()->GethitBox().left, Physics::GetInstance()->GethitBox().top,
		Physics::GetInstance()->GethitBox().right - Physics::GetInstance()->GethitBox().left);

	//��ųâ �������̽� Skill interface toggle
	Interface::GetInstance()->Render(hdc);
	
}

void Interface::Update()
{
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

	if (Input::GetInstance()->GetKey('E')) {
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
	if (mToggleInterface) { //��ųâ �������̽� ���� Skill UI render
		mImage->AlphaFrameRender(hdc, 30, 50, 0, 0,  0.7f);
		mImage->AlphaFrameRender(hdc, 30, 140, 1, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 230, 2, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 320, 3, 0, 0.7f);
	}
	if (mPlayer->GetSkillQTime() > -200) { //��ų Q ��ٿ� üĿ Skill Q cooldown checker
		mImage->AlphaScaleFrameRender(hdc, 1180, 230, 0, 0, 60,60,mAlphaQ);

		wstring Cooldown = to_wstring((300 + mPlayer->GetSkillQTime()) / 100);
		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(60, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &RectMake(1180, 230, 60, 60), DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);

	}

	if (mPlayer->GetSkillWTime() > 0 and mPlayer->GetSkillWTime() < 300) { //��ų W Ȱ�� üĿ Skill W activation checker

		mImage->AlphaScaleFrameRender(hdc, 1030, 10, 1, 0, 50, 50, mAlphaW);

		wstring Cooldown = to_wstring((mPlayer->GetSkillWTime()+100)/100);
		SetTextColor(hdc, RGB(0, 0, 255));
		HFONT newFont = CreateFontW(50, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &RectMake(1030, 10, 50, 50), DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	if (mPlayer->GetSkillWTime() > -500 and mPlayer->GetSkillWTime() < 0) { //��ų W ��ٿ� üĿ Skill W cooldown checker
		mImage->AlphaScaleFrameRender(hdc, 1180, 300, 1, 0, 60, 60, mAlphaW);

		wstring Cooldown = to_wstring((600 + mPlayer->GetSkillWTime()) / 100);
		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(60, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Fixedsys"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		DrawTextW(hdc, Cooldown.c_str(), Cooldown.size(), &RectMake(1180, 300, 60, 60), DT_CENTER and DT_VCENTER);
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	if (Input::GetInstance()->GetKey('E')) { //��ų E Ȱ�� üĿ Skill E activation checker

		mImage->AlphaScaleFrameRender(hdc, 1080, 10, 2, 0, 50,50, mAlphaE);
	}

	if (mPlayer->GetIsDead()) { //��ų R Ȱ�� üĿ Skill R activation checker

		mImage->AlphaFrameRender(hdc, WINSIZEX/2-35, WINSIZEY/2-35, 3, 0, mAlphaR);
	}
	

	//������ : ��ų ���ӽð��� ��ٿ� ���� ������ �����ϴ°� ������ ���ϴ� Skill remaining or cooldown time are better to be setted in variables than constants;
}

void Interface::DamageEffectRender(HDC hdc, float x, float y, float W)
{
	if (mDamageEffectOn) {

		mDamageEffectCount++;
		float Alpha = (float)(51-mDamageEffectCount)/51;

		mMiss->AlphaScaleFrameRender(hdc, x, y - Camera::GetInstance()->GetY(),0, mRandFrameY, W*0.9,W*0.45, Alpha);

		if (mDamageEffectCount > 50) {
			mDamageEffectCount = 0;
			mRandFrameY = Random::GetInstance()->RandInt(3);
			mDamageEffectOn = false;
		}

	}
}
