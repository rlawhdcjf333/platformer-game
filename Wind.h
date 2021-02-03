#pragma once
#include "Map.h"
class Player;
class Wind : public Map
{
	float mAngle;
	float mVec;

	Player* mPlayer;
	int mFrameCount;
	int mFrameX;
	int mFrameY;
	float mAlpha;

public:
	void Init(float x, float y);
	void Update()override;
	void Render(HDC hdc);

	void RotationMatrix();
	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
};

