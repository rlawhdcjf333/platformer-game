#include "pch.h"
#include "Camera.h"
#include "Player.h"
#include "Physics.h"

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

	if (mPlayer->GetonthePlatform() == true and Physics::GetInstance()->GetDamage() > 25) {

		mCameraPanningCount = 0;
		mCameraPanningOn = true;
	}

	CameraPanning();




}

void Camera::CameraPanning()
{

	if (mCameraPanningOn) {

		mCameraPanningCount++;
		if (mCameraPanningCount > 30) {
			mCameraPanningCount = 0;
			mCameraPanningOn = false;
		}

		mAngle = mCameraPanningCount & 1 ? 0.5*PI : 1.5*PI; //비트연산으로 짝홀 계산을 더욱 빠르게
		
		mY -= mVec * sinf(mAngle);
		mRc = RectMake(mX, mY, mW, mH);
	}

}

void Camera::Init()
{

	mW = WINSIZEX;
	mH = WINSIZEY;
	mX = mPlayer->GetX()-mW/2;
	mY = mPlayer->GetY()-mH/2;

	mRc = RectMake(mX, mY, mW, mH);
}