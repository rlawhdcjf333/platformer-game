#pragma once
#include "pch.h"

class Image;
class Player;

class Interface {

	Singleton(Interface)

private:
	Image* mImage = ImageManager::GetInstance()->FindImage(L"InterfaceSkill");
	Image* mMiss = ImageManager::GetInstance()->FindImage(L"Miss");

	Player* mPlayer;

	bool mToggleInterface;
	float mAlphaQ;
	float mAlphaW;
	float mAlphaE;
	float mAlphaR;

	int mRandFrameY;
	bool mDamageEffectOn;
	int mDamageEffectCount;

public:
	void Update();
	void Render(HDC hdc);

	Image* GetImage() { return mImage; }
	bool GetToggleInterface() { return mToggleInterface; }

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }

	void SetDamageEffect(bool torf) { mDamageEffectOn = torf; }
	void DamageEffectRender(HDC hdc, float x, float y, float W);

};