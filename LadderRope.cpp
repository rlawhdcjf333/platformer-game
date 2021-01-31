#include "LadderRope.h"

void LadderRope::Init()
{
	mRc = RectMake(645, -475, 5, 250);
	mRcList.push_back(mRc);

	mRc = RectMake(752, -760, 5, 280);
	mRcList.push_back(mRc);

	mRc = RectMake(75, -1426, 50, 558);
	mRcList.push_back(mRc);

}

void LadderRope::Render(HDC hdc)
{
	//¸ÊÅ¸ÀÏ Ã¼Å·
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

void LadderRope::Release()
{
}

void LadderRope::Update()
{
}
