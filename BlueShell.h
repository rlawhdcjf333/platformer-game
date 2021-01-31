#pragma once
#include "Projectile.h"
class BlueShell : public Projectile
{



public:
	void SetXY(float x, float y) { mX = x, mY = y; }

	void Init(float Vec, float Angle)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

};

