#include "pch.h"
#include "Fixed.h"
#include "Camera.h"

void Fixed::Init()
{
	//...절실하게 맵타일 제작 툴의 필요성을 느끼는 부분;;;

	//맨 밑바닥 렉트
	mRc = RectMake(0, 705, WINSIZEX, 15);
	mRcList.push_back(mRc);

	//(1단계) 한개 씩 올라가는 렉트들
	mRc = RectMake(166, 645, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(1077, 643, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(262, 588, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(988, 588, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(340, 510, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(910, 510, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(428, 448, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(820, 448, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(524, 382, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(724, 382, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(625, 325, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(543, 255, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(705, 255, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(466, 177, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(782, 177, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(376, 115, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(872, 115, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(280, 50, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(969, 50, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(383, -20, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(872, -20, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(465, -88, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(540, -165, 30, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(630, -228,30,10);
	mRcList.push_back(mRc);
	mRc = RectMake(790, -90, 30, 10);
	mRcList.push_back(mRc);

	//1단계 통과 렉트
	mRc = RectMake(610, -475, 88, 10);
	mRcList.push_back(mRc);

	//3단계 달팽이 렉트
	mRc = RectMake(0, -2204, 232, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(270, -2280, 210, 10);
	mRcList.push_back(mRc); 
	mRc = RectMake(535, -2162 - 180, 210,10);
	mRcList.push_back(mRc);
	mRc = RectMake(805, -2164 - 230, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(1070, -2160 - 295, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(888, -2160 - 406, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(630, -2160 - 468, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(355, -2160 - 508, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(100, -2160 - 563, 210, 10);
	mRcList.push_back(mRc);

	//최상층 렉트

	mRc = RectMake(0, -2880 - 48, 210, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(250, -2880 - 102, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(358, -2880 - 158, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(462, -2880 - 212, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(560, -2880 - 266, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(665, -2880 - 318, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(776, -2880 - 364, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(878, -2880 - 404, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(979, -2880 - 447, 38, 10);
	mRcList.push_back(mRc);
	mRc = RectMake(1066, -2880 - 540, 210, 10);
	mRcList.push_back(mRc);
}

void Fixed::Render(HDC hdc)
{	
	//맵타일 체킹
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

void Fixed::Release()
{
}

void Fixed::Update()
{




}
