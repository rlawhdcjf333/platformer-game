#include "main.h"
#include "Image.h"
#include "Player.h"
#include "Physics.h"
#include "WitchCat.h"
#include "YetiAndPepe.h"
#include "MossSnail.h"
#include "Fanzy.h"
#include "Map.h"
#include "Fixed.h"
#include "MovingShell.h"
#include "LadderRope.h"
#include "Slippery.h"
#include "Thorn.h"
#include "Launcher.h"
#include "Aim.h"

void Main::Init() {

	SetTimer(g_hWnd, 1, 10, NULL);

	mBkBuff = new Image();
	mBkBuff->CreateEmpty(WINSIZEX, WINSIZEY);

	ImageManager::GetInstance()->LoadFromFile(L"background", Resources(L"background.bmp"), 1280, 4320, false);
	mBackground = ImageManager::GetInstance()->FindImage(L"background");

	ImageManager::GetInstance()->LoadFromFile(L"Player", Resources(L"Player.bmp"), 320, 1140,4,12,true);
	ImageManager::GetInstance()->LoadFromFile(L"MossSnail", Resources(L"mossSnail.bmp"), 676, 200, 6, 2, true);
	ImageManager::GetInstance()->LoadFromFile(L"WitchCat", Resources(L"witchCat.bmp"), 1000, 600, 10, 6, true);
	ImageManager::GetInstance()->LoadFromFile(L"YetiAndPepe", Resources(L"yetiAndPepe.bmp"), 2250, 500, 9,2, true);
	ImageManager::GetInstance()->LoadFromFile(L"Fanzy", Resources(L"fanzy.bmp"), 1040, 60, 13, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"InvisibleRect", Resources(L"invisibleRect.bmp"), 50, 60, 1, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"GreenShell", Resources(L"greenShell.bmp"), 25, 25, 1, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"BlueShell", Resources(L"blueShell.bmp"), 25, 25, 1, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"RedShell", Resources(L"redShell.bmp"), 25, 25, 1, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"Aim", Resources(L"aim.bmp"), 32,96, 1, 3, true);

	mPlayer = new Player();
	mPlayer->Init();

	Camera::GetInstance()->SetPlayer(mPlayer);
	Camera::GetInstance()->Init();

	Aim::GetInstance()->Init(mPlayer);

	Physics::GetInstance()->SetPlayer(mPlayer);

	Enemy* mEnemy = new WitchCat();
	mEnemy->Init(50, -410);
	mEnemyList.push_back(mEnemy);
	
	mEnemy = new WitchCat();
	mEnemy->Init(1100, -569);
	mEnemyList.push_back(mEnemy);

	mEnemy = new YetiAndPepe();
	mEnemy->Init(900, -2005);
	mEnemyList.push_back(mEnemy);

	mEnemy = new MossSnail();
	mEnemy->Init(600, -2300);
	mEnemyList.push_back(mEnemy);

	mEnemy = new Fanzy();
	mEnemy->Init(0,0);
	mEnemyList.push_back(mEnemy);

	Physics::GetInstance()->SetEnemy(mEnemyList);

	Map* mMap = new Fixed();
	mMap->Init();
	mMapList.push_back(mMap);

	mMap = new LadderRope();
	mMap->Init();
	mMapList.push_back(mMap);

	mMap = new Slippery();
	mMap->Init();
	mMapList.push_back(mMap);

	mMap = new MovingShell();
	mMap->Init();
	mMapList.push_back(mMap);

	mMap = new Thorn();
	mMap->Init();
	mMapList.push_back(mMap);

	mMap = new Launcher();
	mMap->Init();
	mMapList.push_back(mMap);

	Physics::GetInstance()->SetMap(mMapList);
}

void Main::Release() {

	KillTimer(g_hWnd, 1);

	Random::ReleaseInstance();
	
	mPlayer->Release(); 
	SafeDelete(mPlayer);
	
	for (Enemy*& elem : mEnemyList) {

		elem->Release();
		SafeDelete(elem);
	}

	for (Map*& elem : mMapList) {

		elem->Release();
		SafeDelete(elem);
	}
}

void Main::Update() {

	mPlayer->Update();
	
	Camera::GetInstance()->Update();

	for (Enemy* elem : mEnemyList) {
		
		elem->Update();
	}

	for (Map* elem : mMapList) {

		elem->Update();
	}
}

void Main::Render(HDC hdc) {

	HDC backDC = mBkBuff->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); {

		mBackground->Render(backDC, 0 - Camera::GetInstance()->GetX(), 720-4320-Camera::GetInstance()->GetY());
		
		mPlayer->Render(backDC,80,95);

		for (Enemy* elem : mEnemyList) {

			elem->Render(backDC);
		}

		for (Map* elem : mMapList) {

			elem->Render(backDC);
		}
	}

	mBkBuff->Render(hdc, 0, 0);
}


