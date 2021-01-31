#include "pch.h"
#include "Thorn.h"
#include "Camera.h"


void Thorn::Init()
{
	//2단계 얼음지대 가시 함정
	mRc = RectMake(830, -720 - 70, 10, 33);
	mRcList.push_back(mRc);

	mRc = RectMake(600, -720 - 90, 10, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(372, -720 - 126, 10, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(152, -720 - 164, 10, 20);
	mRcList.push_back(mRc);

	mRc = RectMake(152, -720 - 720, 10, 20);
	mRcList.push_back(mRc);
}

void Thorn::Render(HDC hdc)
{
	//맵 타일 위치 체킹용
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

void Thorn::Release()
{
}

void Thorn::Update()
{
}
