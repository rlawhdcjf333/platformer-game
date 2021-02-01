#pragma once
#include "Enemy.h"

class BlueShell;
class Image;

enum class Status1 : int{

	leftIdle,
	Attack
};


class YetiAndPepe:public Enemy
{
	Status1 mStatus;
	vector <BlueShell*> mBlueShellList;

public:
	void Init(float X, float Y)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	inline Status1 const GetStatus() { return mStatus; }
	inline void SetStatus(Status1 newStatus) { mStatus = newStatus; }

	vector <BlueShell*> GetBlueShellList() { return mBlueShellList; }

	void StatusSwitch();
	void EraseBlueShell(BlueShell* blueShellPtr);
};

