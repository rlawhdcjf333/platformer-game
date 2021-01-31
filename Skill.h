#pragma once

class RedShell;

class Skill { //사실상 그냥 redshell Manager;

	float qPower;

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

};