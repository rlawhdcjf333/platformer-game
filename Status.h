#pragma once

enum class Status : int {

	leftIdle,
	rightIdle,
	leftWalk,
	rightWalk,
	leftJump,
	rightJump,
	leftThrow,
	rightThrow,
	leftDown,
	rightDown,
	laddering,
	rope
};

class DeathImage {

	Singleton(DeathImage)
	Image* mImage = ImageManager::GetInstance()->FindImage(L"Death");

public:

	Image* GetImage() { return mImage; }
};
