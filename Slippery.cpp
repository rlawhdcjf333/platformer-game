#include "pch.h"
#include "Slippery.h"
#include "Camera.h"

void Slippery::Init()
{
	//2단계 미끄러운 얼음길 렉트
	mRc = RectMake(750, -720-40, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(990, -720-30, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(525, -720 - 75, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(300, -720 - 110, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(80, -720 - 150, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(75, -720 - 706, 150, 10);
	mRcList.push_back(mRc);

	mRc = RectMake(0, -1400, 33, 10);
	mRcList.push_back(mRc);

	//예티 피하기 렉트~~ 여전히 미끌미끌
	mRc = RectMake(270, -1440 - 45, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(425, -1440 - 50, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(585, -1440 - 50, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(200, -1440 - 130, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(355, -1440 - 130, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(510, -1440 - 130, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(666, -1440 - 130, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(270, -1440 - 215, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(426, -1440 - 215, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(580, -1440 - 220, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(190, -1440 - 300, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(345, -1440 - 300, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(500, -1440 - 300, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(660, -1440 - 300, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(270, -1440 - 380, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(425, -1440 - 385, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(580, -1440 - 385, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(200, -1440 - 470, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(350, -1440 - 470, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(510, -1440 - 470, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(665, -1440 - 470, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(270, -1440 - 550, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(426, -1440 - 550, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(580, -1440 - 550, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(200, -1440 - 636, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(350, -1440 - 636, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(510, -1440 - 636, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(665, -1440 - 636, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(270, -1440 - 720, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(426, -1440 - 725, 70, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(580, -1440 - 725, 70, 20);
	mRcList.push_back(mRc);

	//예티발판

	mRc = RectMake(800, -1440 - 325, 480, 20);
	mRcList.push_back(mRc);
}

void Slippery::Render(HDC hdc)
{
	//맵타일 위치 체킹
	//if (Input::GetInstance()->GetKey(VK_TAB)) {
	//
	//	HBRUSH newBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	//	HPEN newPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	//	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
	//	for (RECT elem : mRcList) {
	//
	//		Rectangle(hdc, elem.left - Camera::GetInstance()->GetX(), elem.top - Camera::GetInstance()->GetY(),
	//			elem.right - Camera::GetInstance()->GetX(), elem.bottom - Camera::GetInstance()->GetY());
	//	}
	//	SelectObject(hdc, oldPen);
	//	DeleteObject(newPen);
	//	SelectObject(hdc, oldBrush);
	//	DeleteObject(newBrush);
	//}
	//else {
	//	HPEN newPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	//	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
	//	for (RECT elem : mRcList) {
	//
	//		Rectangle(hdc, elem.left - Camera::GetInstance()->GetX(), elem.top - Camera::GetInstance()->GetY(),
	//			elem.right - Camera::GetInstance()->GetX(), elem.bottom - Camera::GetInstance()->GetY());
	//	}
	//	SelectObject(hdc, oldPen);
	//	DeleteObject(newPen);
	//}
}

void Slippery::Release()
{
}

void Slippery::Update()
{
}
