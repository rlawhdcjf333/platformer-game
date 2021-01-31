#include "pch.h"
#include "Projectile.h"
#include "Image.h"
#include "Physics.h"

void Projectile::Init(float Vec, float Angle)
{
	mGravity = 0;
	mVec = Vec;
	mAngle = Angle;
}

void Projectile::Render(HDC hdc)
{
}

void Projectile::Release()
{
}

void Projectile::Update()
{
	mGravity += 0.58f;
	mY += mGravity;
	Move();
}

void Projectile::Move()
{
	mX += mVec * cosf(mAngle);
	mY -= mVec * sinf(mAngle);
	mRc = RectMake(mX, mY, mW, mH);
}

