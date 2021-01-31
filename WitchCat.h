#pragma once
#include "Enemy.h"

class Image;
class GreenShell;

enum class Status0 :int {

	leftThrow,
	leftIdle,
	leftHit,
	rightThrow,
	rightIdle,
	rightHit

};

enum class Location : int {

	Left,
	Right

};

class WitchCat : public Enemy
{
	Status0 mStatus;
	Location mLocation;
	vector <GreenShell*> mGreenShellList;
public:

	void Init(float X, float Y)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	inline Status0 const GetStatus() { return mStatus;}
	inline void SetStatus(Status0 newStatus) { mStatus = newStatus; }

	vector <GreenShell*> GetGreenShellList() {return mGreenShellList;}

	void StatusSwitch();
};

