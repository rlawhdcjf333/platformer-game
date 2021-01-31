#pragma once
#include <bitset>

#define KEYMAX 256

class Input
{
public:
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}
private:
	bool mKeyUpList[KEYMAX];		
	bool mKeyDownList[KEYMAX];	
public:
	Input();

	bool GetKeyD(int key);	
	bool GetKeyU(int key);	
	bool GetKey(int key);	
	bool GetTK(int key);	
};
