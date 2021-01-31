#include "GreenShell.h"
#include "Image.h"
#include "Camera.h"

void GreenShell::Init(float Vec, float Angle)
{

	mImage = ImageManager::GetInstance()->FindImage(L"GreenShell");
	Projectile::Init(Vec, Angle);
	mW = mImage->GetWidth();
	mH = mImage->GetHeight();

	mRc = RectMake(mX, mY, mW, mH);


}

void GreenShell::Render(HDC hdc)
{
	mImage->Render(hdc, mRc.left - Camera::GetInstance()->GetX(), mRc.top - Camera::GetInstance()->GetY());
}

void GreenShell::Release()
{
}

void GreenShell::Update()
{

	Projectile::Update();
}
