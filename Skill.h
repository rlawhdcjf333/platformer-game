#pragma once

class RedShell;
class Image;
class Player;

class Skill {

	float qPower;
	Player* mPlayer;
	Image* mImage = ImageManager::GetInstance()->FindImage(L"Clairvoyance");
	vector <RedShell*> mRedShellListQ;
	vector <RedShell*> mRedShellListW;

public:

	vector <RedShell*> GetRedShellListQ() { return mRedShellListQ; };
	inline void AddRedShellQ(RedShell* redShellPtr) { mRedShellListQ.push_back(redShellPtr); }
	void EraseRedShellQ(RedShell* redShellPtr);

	vector <RedShell*> GetRedShellListW() { return mRedShellListW; };
	inline void AddRedShellW (RedShell* redShellPtr) { mRedShellListW.push_back(redShellPtr); }
	void EraseRedShellW (RedShell* redShellPtr);

	void Render(HDC hdc);
	void Release();

	void SetQPower(float size) { qPower = size; }
	float GetQPower() { return qPower; }

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
};