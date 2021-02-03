#pragma once
#include "Map.h"
class Wind : public Map
{
	float mAngle;
	float mVec;


	int mFrameCount;
	int mFrameX;
	int mFrameY;
	float mAlpha;

public:
	void Init(float x, float y);
	void Update()override;
	void Render(HDC hdc);

	void RotationMatrix();
};

