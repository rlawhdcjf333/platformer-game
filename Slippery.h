#pragma once
#include "Map.h"
class Player;
class Wind;
class Slippery :public Map
{
	vector <Wind*> windList;
	Player* mPlayer;

public:
	void Init()override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }

};

