#include "Wind.h"
#include "Image.h"

void Wind::Init(float x, float y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Wind");

	mX = x;
	mY = y;
	mW = mImage->GetFrameWidth();
	mH = mImage->GetFrameHeight();



	mFrameX = 0;
	mFrameY = 0;
	mAlpha = 0;


	mRc = RectMake(mX, mY, mW, mH);

}

void Wind::Update()
{
	mX +=1;
	mY -= 5*sin(2*PI*mX/200);

	RotationMatrix();

	if (mX > WINSIZEX) { mX = -mW; mY = -1 * Random::GetInstance()->RandInt(850, 2200); }

	if (mAlpha > 1) mAlpha = 0;

	mFrameCount++;
	if (mFrameCount > 5) { mFrameCount = 0; mFrameX++, mAlpha += 0.1f; }
	
	if (mFrameX > mImage->GetFrameX()-1) { mFrameX = 0, mFrameY++; }
	if (mFrameY > mImage->GetFrameY()-1) { mFrameY = 0; }

}

void Wind::Render(HDC hdc)
{

	mImage->AlphaScaleFrameRender(hdc, mX, mY - Camera::GetInstance()->GetY(), mFrameX, mFrameY, 165, 105, mAlpha);

}

void Wind::RotationMatrix() //2���� ��ǥ�� ȸ�� ��ȯ 2-D coordinates rotation transform
{
	float Angle = Math::GetAngle(mX, mY, 1350, -1750);
	mX += 1.2 * cosf(Angle);
	mY -= 1.2 * sinf(Angle);
}
