#pragma once
#include "pch.h"

class Image;

class Object
{
protected:

	float mX;
	float mY;
	float mW;
	float mH;

	RECT mRc;

	Image* mImage;

public:

	inline virtual const float GetX() { return mX; }
	inline virtual const float GetY() { return mY; }
	inline virtual void SetX(float X) { mX = X; }
	inline virtual void SetY(float Y) { mY = Y; }

	inline virtual const float GetW() { return mW; }
	inline virtual const float GetH() { return mH; }
	inline virtual const RECT GetRc() { return mRc; }
};

