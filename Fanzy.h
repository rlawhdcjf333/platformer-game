#pragma once
#include "Enemy.h"

class Fanzy : public Enemy
{
	Image* mImage1;

	bool mInvisibility;

	vector<RECT> mRcList;

public:

	void Init(float X, float Y)override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

	bool const GetInvisibility() { return mInvisibility; }
	vector<RECT> GetRcList() { return mRcList; }
};

