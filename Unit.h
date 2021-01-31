#pragma once
#include "Object.h"

class Image;

class Unit :public Object
{
protected:

	float mVec;
	float mAngle;
	int mFrameCount;
	int mFrameX;
	int mFrameY;
	float mAlpha=1;


public:

	inline const float GetVec() { return mVec; }
	inline void SetVec(float Vec) {mVec = Vec;}
	inline const float GetAngle() { return mAngle; }
	inline void SetAngle(float Angle) { mAngle = Angle; }
	inline const int GetFrameCount() { return mFrameCount; }
	inline void SetFrameCount(int FrameCount) { mFrameCount = FrameCount; }
	inline const int GetFrameX() { return mFrameX; }
	inline void SetFrameX(int FrameX) { mFrameX = FrameX; }
	inline const int GetFrameY() { return mFrameY; }
	inline void SetFrameY(int FrameY) { mFrameY = FrameY; }



	void Init(wstring LFileName, float X, float Y);
	virtual void Render(HDC hdc, int ResizeX, int ResizeY);
	void Move();
};

