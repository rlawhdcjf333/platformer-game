#pragma once
#include "Enemy.h"

class Image;

enum class Status2 : int{

	leftMove,
	rightMove
};

struct RcAndRange {

	RECT rc;
	float leftend;
	float rightend = leftend +210;

};

class MossSnail :public Enemy
{
	Status2 mStatus;

	RcAndRange mStruct;
	vector <RcAndRange> mStructList;

public:
	void Init(float X, float Y)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	inline Status2 const GetStatus() { return mStatus; }
	inline void SetStatus(Status2 newStatus) { mStatus = newStatus; }

	vector <RcAndRange> GetSnail() { return mStructList; }


	void StatusSwitch();
};
