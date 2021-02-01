#pragma once
#include "pch.h"

class Image;
class Player;

class Interface {

	Singleton(Interface)

private:
	Image* mImage = ImageManager::GetInstance()->FindImage(L"InterfaceSkill");
	Player* mPlayer;

	bool mToggleInterface;
	float mAlphaQ;
	float mAlphaW;
	float mAlphaE;
	float mAlphaR;

public:
	void Update();
	void Render(HDC hdc);

	Image* GetImage() { return mImage; }
	bool GetToggleInterface() { return mToggleInterface; }

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }

};