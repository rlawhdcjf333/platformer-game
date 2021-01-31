#pragma once
#include "Object.h"


class Map : public Object
{
	Singleton(Map)

protected:
	

	vector <RECT> mRcList;

public:

	inline const vector <RECT> GetMapList() { return mRcList; }

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

};

