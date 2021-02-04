#include "Player.h"
#include "Status.h"
#include "Grendel.h"
#include "Physics.h"

void Player::StatusSwitch()
{
	//»óÅÂ ½ºÀ§Ä¡ , Status Motion Frame Changer
	switch (mStatus) {

	case Status::leftIdle:
		mFrameY = 0;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) mFrameX = 0;
		break;

	case Status::rightIdle:
		mFrameY = 1;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) mFrameX = 0;
		break;

	case Status::leftWalk:
		mFrameY = 2;
		if (mFrameCount > 10) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 3) mFrameX = 0;
		break;

	case Status::rightWalk:
		mFrameY = 3;
		if (mFrameCount > 10) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 3) mFrameX = 0;
		break;

	case Status::leftJump:
		mFrameY = 4;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 1) mFrameX = 0;
		if (onthePlatform == true) { mVec = 0; mStatus = Status::leftIdle; }
		break;

	case Status::rightJump:
		mFrameY = 5;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 1) mFrameX = 0;
		if (onthePlatform == true) { mVec = 0; mStatus = Status::rightIdle; }
		break;

	case Status::leftDown:
		mFrameY = 8;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 1) mFrameX = 0;
		break;

	case Status::rightDown:
		mFrameY = 9;
		if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 1) mFrameX = 0;
		break;

	case Status::leftThrow:
		mFrameY = 6; mVec = 0; onthePlatform = true;
		if (mFrameCount > 15) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) { mFrameX = 0; mStatus = Status::leftIdle;  }
		break;

	case Status::rightThrow:
		mFrameY = 7; mVec = 0; onthePlatform = true;
		if (mFrameCount > 15) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) { mFrameX = 0; mStatus = Status::rightIdle;  }
		break;

	case Status::laddering:
		mFrameY = 10;
		if (Input::GetInstance()->GetKey(VK_UP) or Input::GetInstance()->GetKey(VK_DOWN)) {
			if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
			if (mFrameX > 1) mFrameX = 0;
		}
		break;

	case Status::rope:
		mFrameY = 11;
		if (Input::GetInstance()->GetKey(VK_UP) or Input::GetInstance()->GetKey(VK_DOWN)) {
			if (mFrameCount > 20) { mFrameCount = 0, mFrameX++; }
			if (mFrameX > 1) mFrameX = 0;
		}
		break;
	}
}

void Player::DeathAnimation() {

	mFrameCount++;
	mImage = DeathImage::GetInstance()->GetImage(); mFrameY = 0;
	if (mFrameCount > 10) { mFrameCount = 0; mFrameX++; }
	if (mFrameX > 5) mFrameX = 5;

	//ºÎÈ° ±×·»µ¨ ÅÂÃÊ ±ÍÈ¯ , resurrection, summon Grendel, return to archeage
	if (Input::GetInstance()->GetKeyD('R')) { 
		IsDead = false; mImage = ImageManager::GetInstance()->FindImage(L"Player");
		mX = WINSIZEX / 2-40, mY = 550; mRc = RectMake(mX, mY, mW, mH);
		mStatus = Status::leftIdle; mFrameX = 1; mVec = 0; 
		mHP = 1000, mMP = 1000;
		Physics::GetInstance()->SetDamage(0);
		mGrendel = new Grendel();
		mGrendel->Init(mX-50, mY - 200);
	}

}