#pragma once
#include "pch.h"

class Image;
class Player;

class Interface {

	Singleton(Interface)

private:
	Image* mImage = ImageManager::GetInstance()->FindImage(L"InterfaceSkill");
	Image* mCaution = ImageManager::GetInstance()->FindImage(L"Caution");
	Image* mMiss = ImageManager::GetInstance()->FindImage(L"Miss");
	Image* mInterface = ImageManager::GetInstance()->FindImage(L"Interface");
	Image* mHpBar = ImageManager::GetInstance()->FindImage(L"HpBar");
	Image* mMpBar = ImageManager::GetInstance()->FindImage(L"MpBar");
	Image* mNumbers = ImageManager::GetInstance()->FindImage(L"Numbers");

	Player* mPlayer;
	int mLevel;

	bool mToggleInterface=true;
	float mAlphaQ;
	float mAlphaW;
	float mAlphaE;
	float mAlphaR;

	int mRandFrameY;
	bool mDamageEffectOn;
	int mDamageEffectCount;

	bool mHpDamageEffectOn;
	int mHpDamageEffectCount;
	int tempHP;
	int mDamage;

public:
	void Update();
	void Render(HDC hdc);

	Image* GetImage() { return mImage; }
	bool GetToggleInterface() { return mToggleInterface; }

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }

	void SetDamageEffect(bool torf) { mDamageEffectOn = torf; }
	void DamageEffectRender(HDC hdc, float x, float y, float W);
	void PlayerDamageEffectRender(HDC hdc, int damage);
};