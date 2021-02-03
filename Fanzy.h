#pragma once
#include "Enemy.h"
class Player;
class Fanzy : public Enemy
{
	Image* mImage1;

	bool mInvisibility;

	vector<RECT> mRcList;

	Player* mPlayer;
public:

	void Init(float X, float Y)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	bool const GetInvisibility() { return mInvisibility; }
	vector<RECT> GetRcList() { return mRcList; }
};

