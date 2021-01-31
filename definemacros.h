#pragma once

#define PI 3.141592

//WINSIZE
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX  1280
#define WINSIZEY 720

//dynamic alloc release macro
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//Singleton macro
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

//image resource pathfinder
#define Resources(Path) (wstring(L"Resources/").append(Path))

//class var macro
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}