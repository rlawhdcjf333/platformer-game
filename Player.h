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
	bool IsDead;
	
	bool SkillQ;
	int SkillQTime;
	bool SkillW;
	int SkillWTime;

	int mHP;
	int mMP;

public:

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc, int ResizeX, int ResizeY)override;

	inline int const GetHP() { return mHP; }
	inline int const GetMP() { return mMP; }
	inline void SetHP(int hpValue) { mHP = hpValue; }
	inline void SetMP(int mpValue) { mMP = mpValue; }

	void PlayerInput();
	void StatusSwitch();
	inline Status const GetStatus() { return mStatus; }
	inline void SetStatus(Status StatusX) { mStatus = StatusX; }

	inline bool const GetonthePlatform() { return onthePlatform; }
	inline void SetonthePlatform(bool bools) { onthePlatform = bools; }

	inline bool const GetontheLadder() { return ontheLadder; }
	inline void SetontheLadder(bool bools) { ontheLadder = bools; }

	inline bool const GetontheRope() { return ontheRope; }
	inline void SetontheRope(bool bools) { ontheRope = bools; }

	Skill* GetSkill() { return mSkill; }
	void istheSkill();

	inline bool const GetIsDead() { return IsDead; }
	inline void SetIsDead(bool trueOrFalse) { IsDead = trueOrFalse; }

	void DeathAnimation();

	int const GetSkillQTime() { return SkillQTime; }
	int const GetSkillWTime() { return SkillWTime; }
};

