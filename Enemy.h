#pragma once
#include "Unit.h"

class Enemy :public Unit 
{
protected:


public:

	virtual void Init(float X, float Y);
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual void Update();

};

