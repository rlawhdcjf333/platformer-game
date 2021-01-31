#pragma once
#include "Map.h"

class Fixed :public Map
{

public:

	void Init()override;
	void Render(HDC hdc)override;
	void Release()override;
	void Update()override;
};

