#include "Player.h"
#include "Fixed.h"

void Player::StatusSwitch()
{
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
		mFrameY = 6;
		if (mFrameCount > 10) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) mFrameX = 0;
		break;

	case Status::rightThrow:
		mFrameY = 7;
		if (mFrameCount > 10) { mFrameCount = 0, mFrameX++; }
		if (mFrameX > 2) mFrameX = 0;
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

