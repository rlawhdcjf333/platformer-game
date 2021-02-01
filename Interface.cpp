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

		mBkBuff->ScaleRender(hdc, 1170, 20, 80, 130); 
	}

	//낙사 주의 Fall death alert
	if (Physics::GetInstance()->GetG() > 25) {

		wstring Alert = L"주의!"; //주의
		if (Physics::GetInstance()->GetG() > 35) Alert = L"사망!";//확정 사망

		SetTextColor(hdc, RGB(255, 0, 0));
		HFONT newFont = CreateFontW(100, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("돋움"));
		HFONT oldFont = (HFONT)SelectObject(hdc, newFont);
		TextOut(hdc, 50, 300, Alert.c_str(), Alert.size());
		SelectObject(hdc, oldFont);
		DeleteObject(newFont);
	}

	//스킬창 인터페이스 Skill interface toggle
	Interface::GetInstance()->Render(hdc);
	
}

void Interface::Update()
{
	if (Input::GetInstance()->GetKeyD('S')) { mToggleInterface = !mToggleInterface; }

	if (Input::GetInstance()->GetKey('E')) {
		if (mAlphaE > 0.7f) mAlphaE = 0.3f;
		mAlphaE += 0.01f;
	}
	else mAlphaE = 0.7f;

	if (mPlayer->GetIsDead()) {
		if (mAlphaR > 0.9f) mAlphaR = 0.2f;
		mAlphaR += 0.01f;
	}
	else mAlphaR = 0.7f;
}

void Interface::Render(HDC hdc)
{
	if (mToggleInterface) {
		mImage->AlphaFrameRender(hdc, 30, 50, 0, 0,  0.7f);
		mImage->AlphaFrameRender(hdc, 30, 140, 1, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 230, 2, 0, 0.7f);
		mImage->AlphaFrameRender(hdc, 30, 320, 3, 0, 0.7f);
	}

	if (Input::GetInstance()->GetKey('E')) {
		mImage->AlphaFrameRender(hdc, 1180, 230, 2, 0, mAlphaE);
	}

	if (mPlayer->GetIsDead()) {
		mImage->AlphaFrameRender(hdc, WINSIZEX/2-35, WINSIZEY/2-35, 3, 0, mAlphaR);
	}
	
}
