#pragma once
#include "Map.h"

class Image;




class MovingShell :public Map
{

	float mAngle;

	float mRadius;


public:

	void Init()override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

};

