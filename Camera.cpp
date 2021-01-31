#include "pch.h"
#include "Camera.h"
#include "Player.h"

void Camera::Update()
{
	
	mX = mPlayer->GetX()- mW/2;
	mY = mPlayer->GetRc().top - mH/2;
	mRc = RectMake(mX, mY, mW, mH);

	if (mRc.left < 0) mX = 0;
	if (mRc.right > WINSIZEX) mX = 0;
	if (mRc.bottom > WINSIZEY) mY = 0;
	if (mRc.top < WINSIZEY - 4320) mY = WINSIZEY - 4320;

	mRc = RectMake(mX, mY, mW, mH);

}

void Camera::Init()
{

	mW = WINSIZEX;
	mH = WINSIZEY;
	mX = mPlayer->GetX()-mW/2;
	mY = mPlayer->GetY()-mH/2;

	mRc = RectMake(mX, mY, mW, mH);
}