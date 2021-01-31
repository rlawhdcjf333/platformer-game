#include "BlueShell.h"
#include "Image.h"
#include "Camera.h"

void BlueShell::Init(float Vec, float Angle)
{

	mImage = ImageManager::GetInstance()->FindImage(L"BlueShell");
	Projectile::Init(Vec, Angle);
	mW = mImage->GetWidth();
	mH = mImage->GetHeight();

	mRc = RectMake(mX, mY, mW, mH);


}

void BlueShell::Render(HDC hdc)
{
	mImage->Render(hdc, mRc.left-Camera::GetInstance()->GetX(), mRc.top-Camera::GetInstance()->GetY());
}

void BlueShell::Release()
{
}

void BlueShell::Update()
{

	Projectile::Update();
}
