#pragma once
#include "pch.h"

class Image;
class Player;
class Enemy;
class Map;
class Projectile;

class Main
{
	Image* mBkBuff;

private:

	Image* mBackground;
	Player* mPlayer;

	vector<Enemy*> mEnemyList;

	vector<Map*> mMapList;

	vector <Projectile*> mProjectileList;

	bool mToggeleMiniMap=true;
	
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void InterfaceRender(HDC hdc);
};

