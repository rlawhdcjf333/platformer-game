#pragma once
#include "Map.h"

class BlueShell;
class Launcher :public Map
{
	int mFiringPower;
	int mLaunchCount;
	map <string, BlueShell*> mLauncherList;

public:
	void Init()override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	map <string, BlueShell*> GetLauncherList() { return mLauncherList; }
};

