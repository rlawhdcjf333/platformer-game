#pragma once
#include "Projectile.h"
class RedShell : public Projectile
{
	Player* mPlayer;


public:
	void SetXY(float x, float y) { mX = x, mY = y; }

	void Init(float Vec, float Angle)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;



};
