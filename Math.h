#pragma once

class Math
{

public:

	static float GetAngle(float x, float y, float xx, float yy);

	static float Distance(float x, float y, float xx, float yy);

	static float Dot(float x, float y, float x1, float y1, float x2, float y2); // x,y ���� ����; 

	static float GetDotAngle(float x, float y, float x1, float y1, float x2, float y2);// ���� ���̰� ���;
};


