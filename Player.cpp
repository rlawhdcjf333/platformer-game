#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Physics.h"
#include "Map.h"
#include "Skill.h"
#include "Aim.h"
#include "Grendel.h"
#include "Interface.h"

void Player::Init()
{

	Unit::Init(L"Player", WINSIZEX/2-40, 500);
	Aim::GetInstance()->Init(this);
	Interface::GetInstance()->SetPlayer(this);

	mHP = 1000;
	mMP = 1000;
	mSkill = new Skill();
	mSkill->SetPlayer(this); 
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

	SafeDelete(mGrendel)
}

void Player::Update()
{
	//죽음과 부활 @ StatusSwitch cpp, Death and Resurrection
	if (mHP < 0) { IsDead = true;}
	if (IsDead) {
		mHP = 0;
		DeathAnimation();
		return;
	}
	if (mGrendel != NULL) {
		mGrendel->Update();
		if (mGrendel->GetFrameX() == 2 and mGrendel->GetFrameCount() == 25) SafeDelete(mGrendel)
	}

	if(mMP<1000 and mFrameCount==10) mMP++;

	//오브젝트 충돌 판정 @ Singleton Physics cpp, MapObject Collision 
	Physics::GetInstance()->IsonthePlatform(); 

	//키입력 처리 @ PlayerInput cpp,  Key input
	PlayerInput();

	//상태 처리 @ StatusSwitch cpp, Status management
	mFrameCount++;
	StatusSwitch();
	
	//스킬 처리 @ Skill cpp, Skill management
	istheSkill();

	//움직임, 피격, 중력 처리 @ Singleton Physics cpp, OnHit, gravity, movement
	Physics::GetInstance()->IstheHit();
	Physics::GetInstance()->PhysicsUpdate(); 
	Move();

	//위치 보정 relocation
	if (mRc.bottom > WINSIZEY-15) { mY = WINSIZEY - 105; } //화면 바닥, Bottomline
	if (mRc.right > WINSIZEX) { mX = WINSIZEX - mW, mAngle = PI - mAngle; } //오른쪽, Rightend
	if (mRc.left < 0) { mX = 0, mAngle = PI - mAngle; } //왼쪽, Leftend

	//제작용 치트키 CheatKey
	if (Input::GetInstance()->GetKey('O')) { mY-=15;Physics::GetInstance()->SetG(-0.58f);}
	if (Input::GetInstance()->GetKey('L')) { mY += 21; onthePlatform = false; }

	//렉트 보정 Redrawing Rect (to escape from shaking)
	mRc = RectMake(mX, mY, mW, mH); 
}

void Player::Render(HDC hdc, int ResizeX, int ResizeY)
{
	//부활 그렌델 이펙트 렌더 Grendel E
	if(mGrendel!=NULL) mGrendel->Render(hdc);
	//플레이어 렌더 Player
	Unit::Render(hdc,ResizeX, ResizeY);
	//스킬 이펙트 렌더 Skill E
	mSkill->Render(hdc);
	//조준선 렌더 Aim Object
	if(SkillQ==true) Aim::GetInstance()->Render(hdc);
}


