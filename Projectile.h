#pragma once
#include "Object.h"

class Image;

class Projectile :public Object
{
	float mVec;
	float mAngle;
	float mGravity;

public:

	virtual void Init(float Vec, float Angle);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void Update();

	void Move();

};

