#pragma once

class Player;

class Camera
{
	Singleton(Camera)

private:
	float mX;
	float mY;
	float mW = WINSIZEX;
	float mH = WINSIZEY;

	float mAngle;
	float mVec=5;
	
	bool mCameraPanningOn;
	int mCameraPanningCount;

	RECT mRc;
	Player* mPlayer;

public:

	void Init();
	void Update();
	void CameraPanning();

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }

	inline const float GetX() { return mX; }
	inline const float GetY() { return mY; }
	inline const RECT GetRc() { return mRc; }
};

