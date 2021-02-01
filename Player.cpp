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

	Interface::GetInstance()->SetPlayer(this);
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
	//������Ʈ �浹 ���� @ Singleton Physics cpp, MapObject Collision 
	Physics::GetInstance()->IsonthePlatform(); 

	//������ ��Ȱ @ StatusSwitch cpp, Death and Resurrection
	if (IsDead == true) {
		DeathAnimation();
		return;
	}
	if (mGrendel != NULL) {
		mGrendel->Update();
		if (mGrendel->GetFrameX() == 2 and mGrendel->GetFrameCount() == 25) SafeDelete(mGrendel)
	}
	//Ű�Է� ó�� @ PlayerInput cpp,  Key input
	PlayerInput();

	//���� ó�� @ StatusSwitch cpp, Status management
	mFrameCount++;
	StatusSwitch();
	
	//��ų ó�� @ Skill cpp, Skill management
	istheSkill();

	//������, �ǰ�, �߷� ó�� @ Singleton Physics cpp, OnHit, gravity, movement
	Physics::GetInstance()->IstheHit();
	Physics::GetInstance()->PhysicsUpdate(); 
	Move();

	//��ġ ���� relocation
	if (mRc.bottom > WINSIZEY-15) { mY = WINSIZEY - 105; } //ȭ�� �ٴ�, Bottomline
	if (mRc.right > WINSIZEX) { mX = WINSIZEX - mW, mAngle = PI - mAngle; } //������, Rightend
	if (mRc.left < 0) { mX = 0, mAngle = PI - mAngle; } //����, Leftend

	//���ۿ� ġƮŰ CheatKey
	if (Input::GetInstance()->GetKey('O')) { mY-=15;Physics::GetInstance()->SetG(-0.58f);}
	if (Input::GetInstance()->GetKey('L')) { mY += 21; onthePlatform = false; }

	//��Ʈ ���� Redrawing Rect (to escape from shaking)
	mRc = RectMake(mX, mY, mW, mH); 
}

void Player::Render(HDC hdc, int ResizeX, int ResizeY)
{
	//��Ȱ �׷��� ����Ʈ ���� Grendel E
	if(mGrendel!=NULL) mGrendel->Render(hdc);
	//�÷��̾� ���� Player
	Unit::Render(hdc,ResizeX, ResizeY);
	//��ų ����Ʈ ���� Skill E
	mSkill->Render(hdc);
	//���ؼ� ���� Aim Object
	if(SkillQ==true) Aim::GetInstance()->Render(hdc);
}


