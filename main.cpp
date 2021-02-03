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
#include "Interface.h"

void Main::Init() {

	SetTimer(g_hWnd, 1, 10, NULL);

	mBkBuff = new Image();
	mBkBuff->CreateEmpty(WINSIZEX, WINSIZEY+40);

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
	ImageManager::GetInstance()->LoadFromFile(L"Death", Resources(L"death.bmp"), 462, 38, 6, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"Grendel", Resources(L"grendel.bmp"), 276, 154, 3, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"Clairvoyance", Resources(L"clairvoyance.bmp"), 50, 52, 1, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"InterfaceSkill", Resources(L"interfaceSkill.bmp"),280,70, 4, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"Miss", Resources(L"missE.bmp"), 65, 93,1,3, true);
	ImageManager::GetInstance()->LoadFromFile(L"Stun", Resources(L"stun.bmp"), 170, 21, 5, 1, true);
	ImageManager::GetInstance()->LoadFromFile(L"Interface", Resources(L"interface.bmp"),1280, 40, false);
	ImageManager::GetInstance()->LoadFromFile(L"HpBar", Resources(L"hpBar.bmp"), 226, 40, true);
	ImageManager::GetInstance()->LoadFromFile(L"MpBar", Resources(L"mpBar.bmp"), 230, 40, true);
	ImageManager::GetInstance()->LoadFromFile(L"Numbers", Resources(L"numbers.bmp"), 360, 74, 10, 2,true);
	ImageManager::GetInstance()->LoadFromFile(L"Caution", Resources(L"caution.bmp"), 120, 120, true);
	ImageManager::GetInstance()->LoadFromFile(L"Wind", Resources(L"wind2.bmp"), 100 , 68 , 1 , 1 , true);

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
	Fanzy* temp = (Fanzy*)mEnemy; //임시 다운캐스팅
	temp->SetPlayer(mPlayer);
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
	Slippery* mSlippery = (Slippery*)mMap;
	mSlippery->SetPlayer(mPlayer);
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
	
	Interface::GetInstance()->Update();

	mPlayer->Update();
	
	Camera::GetInstance()->Update();

	for (Enemy* elem : mEnemyList) {
		
		elem->Update();
	}
	for (Map* elem : mMapList) {

		elem->Update();
	}

	//미니맵 토글 Toggel minimap
	if (Input::GetInstance()->GetKeyD('M')) { mToggeleMiniMap = !mToggeleMiniMap; } 
}

void Main::Render(HDC hdc) {

	HDC backDC = mBkBuff->GetHDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS); {

		mBackground->Render(backDC, 0 - Camera::GetInstance()->GetX(), 720-4320-Camera::GetInstance()->GetY());
		
		mPlayer->Render(backDC,80,95);

		for (Enemy* elem : mEnemyList) {
			if(elem->GetY()>Camera::GetInstance()->GetY() and elem->GetY()<Camera::GetInstance()->GetY()+720)
			elem->Render(backDC);
		}

		for (Map* elem : mMapList) {
			//if (elem->GetY() > Camera::GetInstance()->GetY() and elem->GetY() < Camera::GetInstance()->GetY() + 720)
			elem->Render(backDC);
		}

		InterfaceRender(backDC);

		
	}

	mBkBuff->Render(hdc, 0, 0);

}

