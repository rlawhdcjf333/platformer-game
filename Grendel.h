#pragma once
#include "Unit.h"

class Grendel :public Unit
{
	float mAlpha;


public:

	void Init(float x, float y);
	void Update();
	void Render(HDC hdc);
	
};

