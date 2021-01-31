#include "RedShell.h"
#include "Image.h"
#include "Camera.h"

void RedShell::Init(float Vec, float Angle)
{

	mImage = ImageManager::GetInstance()->FindImage(L"RedShell");
	Projectile::Init(Vec, Angle);
	mW = mImage->GetWidth();
	mH = mImage->GetHeight();

	mRc = RectMake(mX, mY, mW, mH);

}

void RedShell::Render(HDC hdc)
{
	mImage->Render(hdc, mRc.left - Camera::GetInstance()->GetX(), mRc.top - Camera::GetInstance()->GetY());

}

void RedShell::Release()
{
}

void RedShell::Update()
{
	Projectile::Update();

}
