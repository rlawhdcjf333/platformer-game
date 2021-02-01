#pragma once
#include "Projectile.h"
class Player;

class Aim :public Projectile
{
	Singleton(Aim)

	float mAngle;
	int mFrameX;
	int mFrameY;
	
	Player* mPlayer;
	POINT trajecLine[20];

public:

	void Init(Player* playerPtr);
	void On();
	void Render(HDC hdc)override;
	void Off();

	float GetAimAngle() { return mAngle; }
};

