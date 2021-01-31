#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Physics.h"
#include "Map.h"
#include "Skill.h"
#include "Aim.h"

void Player::Init()
{

	Unit::Init(L"Player", 70, -1000);

	mSkill = new Skill();
	mVec = 0;
	mAngle = 0;
	mFrameCount = 0;
	SkillQTime = -200;
	SkillWTime = -500;

	mStatus = Status::rightIdle;

}

void Player::Release()
{
	mSkill->Release();
	SafeDelete(mSkill)
}

void Player::Update()
{

	Physics::GetInstance()->IsonthePlatform(); //오브젝트 충돌 판정

	if (onthePlatform == true) { //걷기와 점프  --->인풋 조작도 사실 그냥 따로 클래스로 뺄 수 있을듯?
		if (mStatus != Status::leftWalk and Input::GetInstance()->GetKeyD(VK_RIGHT)) { mStatus = Status::rightWalk; }
		if ((mStatus == Status::rightWalk or mStatus == Status::rightIdle) and Input::GetInstance()->GetKey(VK_RIGHT)) 
		{ mStatus = Status::rightWalk; mVec = 3; mAngle = 0; }
		if (mStatus == Status::rightWalk and Input::GetInstance()->GetKeyU(VK_RIGHT)) { mStatus = Status::rightIdle; mVec = 0; }

		if (mStatus != Status::rightWalk and Input::GetInstance()->GetKeyD(VK_LEFT)) { mStatus = Status::leftWalk; }
		if ((mStatus == Status::leftWalk or mStatus == Status::leftIdle) and Input::GetInstance()->GetKey(VK_LEFT))
		{ mStatus = Status::leftWalk; mVec = 3; mAngle = PI; }
		if (mStatus == Status::leftWalk and Input::GetInstance()->GetKeyU(VK_LEFT)) { mStatus = Status::leftIdle; mVec = 0; }

		if (Input::GetInstance()->GetKeyD(VK_SPACE)) {

			if (mStatus == Status::rightIdle) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.5; onthePlatform = false; }
			if (mStatus == Status::leftIdle) { mStatus = Status::leftJump;  mVec = 10; mAngle = PI * 0.5; onthePlatform = false; }
			if (Input::GetInstance()->GetKey(VK_RIGHT)) {mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.35; onthePlatform = false;}
			if (Input::GetInstance()->GetKey(VK_LEFT)) { mStatus = Status::leftJump, mVec = 10, mAngle = PI * 0.65; onthePlatform = false; }
		}
		//엎드려
		if ( Input::GetInstance()->GetKey(VK_DOWN)) {
			if (mStatus == Status::rightWalk or mStatus == Status::rightIdle) { mStatus = Status::rightDown; mVec =0; }
			if (mStatus == Status::leftWalk or mStatus == Status::leftIdle) { mStatus = Status::leftDown; mVec = 0; }
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

		if (Input::GetInstance()->GetKeyD(VK_DOWN)) { mStatus = Status::laddering; onthePlatform = false;}
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
		if (Input::GetInstance()->GetKeyU(VK_UP)) { mVec = 0; mFrameX = 0;}

		if (Input::GetInstance()->GetKeyD(VK_DOWN)) { mStatus = Status::rope; onthePlatform = false; }
		if (Input::GetInstance()->GetKey(VK_DOWN)) { mY++; }
		if (Input::GetInstance()->GetKeyU(VK_DOWN)) { mVec = 0; mFrameX = 0;}

		if (Input::GetInstance()->GetKeyD(VK_SPACE)) {
			if (Input::GetInstance()->GetKey(VK_RIGHT)) { mStatus = Status::rightJump, mVec = 10, mAngle = PI * 0.35; ontheLadder = false; }
			if (Input::GetInstance()->GetKey(VK_LEFT)) { mStatus = Status::leftJump, mVec = 10, mAngle = PI * 0.65; ontheLadder = false; }
		}
	}

	if (mStatus == Status::rope and ontheRope == false) { mStatus = Status::leftIdle; }


	//제작용 치트키
	//if (Input::GetInstance()->GetKey('O')) { mY-=15;}
	//if (Input::GetInstance()->GetKey('L')) { mY+=15; }

	//상태 처리
	mFrameCount++;
	StatusSwitch();
	
	//스킬 처리
	istheSkill();

	//움직임 및 중력 처리
	Physics::GetInstance()->IstheHit(); //피격 판정
	Physics::GetInstance()->PhysicsUpdate(); //얘가 중력가속을 처리
	Move();//델타 t 순간 벡터와 앵글에 따른 적절한 좌표 이동 처리


	//보정 구간
	//맨 밑바닥은 렉트충돌과 관계 없이 보정 필요함. 안 그러면 중력가속 때문에 그냥 화면 밑으로 빠지는 참사 발생;
	if (mRc.bottom > WINSIZEY - 10) { mY = WINSIZEY - 105, Physics::GetInstance()->SetG(-0.58f); }
	if (mRc.right > WINSIZEX) { mX = WINSIZEX - mW, mAngle = PI - mAngle; }
	if (mRc.left < 0) { mX = 0, mAngle = PI - mAngle; }
	
	
	//제작용 치트키
	//Physics::GetInstance()->SetG(-0.58f);

	mRc = RectMake(mX, mY, mW, mH);
}

void Player::Render(HDC hdc, int ResizeX, int ResizeY)
{
	Unit::Render(hdc, ResizeX, ResizeY);
	if(SkillQ==true) Aim::GetInstance()->Render(hdc);
	mSkill->Render(hdc);
}


