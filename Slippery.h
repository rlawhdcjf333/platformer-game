#pragma once
#include "Map.h"

class Wind;
class Slippery :public Map
{
	vector <Wind*> windList;

public:
	void Init()override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;

};

