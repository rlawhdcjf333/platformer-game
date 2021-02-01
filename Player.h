#pragma once
#include "Unit.h"
#include "Status.h"

class Image;
class Skill;
class Grendel;

class Player :public Unit
{
	Status mStatus;
	Skill* mSkill;
	Grendel* mGrendel;

	bool onthePlatform;
	bool ontheLadder;
	bool ontheRope;
	
	bool SkillQ;
	int SkillQTime;
	bool SkillW;
	int SkillWTime;
	bool IsDead;

public:

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc, int ResizeX, int ResizeY)override;

	void PlayerInput();
	void StatusSwitch();
	inline Status const GetStatus() { return mStatus; }
	inline void SetStatus(Status StatusX) { mStatus = StatusX; }

	bool GetonthePlatform() { return onthePlatform; }
	void SetonthePlatform(bool bools) { onthePlatform = bools; }

	bool GetontheLadder() { return ontheLadder; }
	void SetontheLadder(bool bools) { ontheLadder = bools; }

	bool GetontheRope() { return ontheRope; }
	void SetontheRope(bool bools) { ontheRope = bools; }

	void istheSkill();

	Skill* GetSkill() { return mSkill; }

	void SetIsDead(bool trueOrFalse) { IsDead = trueOrFalse; }
	void DeathAnimation();
};

