#include "Player.h"

void Player::PlayerInput() {

	if (onthePlatform == true) { //걷기와 점프 
		if (mStatus != Status::leftWalk and Input::GetInstance()->GetKeyD(VK_RIGHT)) { mStatus = Status::rightWalk; }
		if ((mStatus == Status::rightWalk or mStatus == Status::rightIdle) and Input::GetInstance()->GetKey(VK_RIGHT))
		{
			mStatus = Status::rightWalk; mVec = 3; mAngle = 0;
		}
		if (mStatus == Status::rightWalk and Input::GetInstance()->GetKeyU(VK_RIGHT)) { mStatus = Status::rightIdle; mVec = 0; }

		if (mStatus != Status::rightWalk and Input::GetInstance()->GetKeyD(VK_LEFT)) { mStatus = Status::leftWalk; }
		if ((mStatus == Status::leftWalk or mStatus == Status::leftIdle) and Input::GetInstance()->GetKey(VK_LEFT))
		{
			mStatus = Status::leftWalk; mVec = 3; mAngle = PI;
		}
		if (mStatus == Status::leftWalk and Input::GetInstance()->GetKeyU(VK_LEFT)) { mStatus = Status::leftIdle; mVec = 0; }

		if (Input::GetInstance()->GetKeyD(VK_SPACE)) {

			if (mStatus == Status::rightIdle) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.5; onthePlatform = false; }
			if (mStatus == Status::leftIdle) { mStatus = Status::leftJump;  mVec = 10; mAngle = PI * 0.5; onthePlatform = false; }
			if (Input::GetInstance()->GetKey(VK_RIGHT)) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.35; onthePlatform = false; }
			if (Input::GetInstance()->GetKey(VK_LEFT)) { mStatus = Status::leftJump, mVec = 10, mAngle = PI * 0.65; onthePlatform = false; }
		}
		//엎드려
		if (Input::GetInstance()->GetKey(VK_DOWN)) {
			if (mStatus == Status::rightWalk or mStatus == Status::rightIdle) { mStatus = Status::rightDown; mVec = 0; }
			if (mStatus == Status::leftWalk or mStatus == Status::leftIdle) { mStatus = Status::leftDown; mVec = 0; }
			if (mStatus == Status::rightDown and Input::GetInstance()->GetKey(VK_SPACE))
			{
				mY += 21; onthePlatform = false; mStatus = Status::rightJump;
			}
			if (mStatus == Status::leftDown and Input::GetInstance()->GetKey(VK_SPACE))
			{
				mY += 21; onthePlatform = false; mStatus = Status::leftJump;
			}
		}
		// 엎드려 기상
		if (Input::GetInstance()->GetKeyU(VK_DOWN)) {
			if (mStatus == Status::rightDown) { mStatus = Status::rightIdle; }
			if (mStatus == Status::leftDown) { mStatus = Status::leftIdle; }
		}


	}

	if (ontheLadder == true) { //사다리 타기
		if (Input::GetInstance()->GetKeyD(VK_UP)) { mStatus = Status::laddering; onthePlatform = false; }
		if (Input::GetInstance()->GetKey(VK_UP)) { mY--; }
		if (Input::GetInstance()->GetKeyU(VK_UP)) { mVec = 0; mFrameX = 0; }

		if (Input::GetInstance()->GetKeyD(VK_DOWN)) { mStatus = Status::laddering; onthePlatform = false; }
		if (Input::GetInstance()->GetKey(VK_DOWN)) { mY++; }
		if (Input::GetInstance()->GetKeyU(VK_DOWN)) { mVec = 0; mFrameX = 0; }

		if (Input::GetInstance()->GetKeyD(VK_SPACE)) {
			if (Input::GetInstance()->GetKey(VK_RIGHT)) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.35; ontheLadder = false; }
			if (Input::GetInstance()->GetKey(VK_LEFT)) { mStatus = Status::leftJump, mVec = 10, mAngle = PI * 0.65; ontheLadder = false; }
		}
	}

	if (mStatus == Status::laddering and ontheLadder == false) { mStatus = Status::leftIdle; }

	if (ontheRope == true) { //로프 타기
		if (Input::GetInstance()->GetKeyD(VK_UP)) { mStatus = Status::rope; onthePlatform = false; }
		if (Input::GetInstance()->GetKey(VK_UP)) { mY--; }
		if (Input::GetInstance()->GetKeyU(VK_UP)) { mVec = 0; mFrameX = 0; }

		if (Input::GetInstance()->GetKeyD(VK_DOWN)) { mStatus = Status::rope; onthePlatform = false; }
		if (Input::GetInstance()->GetKey(VK_DOWN)) { mY++; }
		if (Input::GetInstance()->GetKeyU(VK_DOWN)) { mVec = 0; mFrameX = 0; }

		if (Input::GetInstance()->GetKeyD(VK_SPACE)) {
			if (Input::GetInstance()->GetKey(VK_RIGHT)) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.35; ontheLadder = false; }
			if (Input::GetInstance()->GetKey(VK_LEFT)) { mStatus = Status::leftJump, mVec = 10, mAngle = PI * 0.65; ontheLadder = false; }
		}
	}

	if (mStatus == Status::rope and ontheRope == false) { mStatus = Status::leftIdle; }


}
