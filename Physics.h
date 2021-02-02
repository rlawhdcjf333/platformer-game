#pragma once

class Player;
class Projectile;
class Map;
class Enemy;

class Physics
{
	Singleton(Physics) //모든 충돌처리는 Physics 싱글턴이 처리한다

	float mGravity;
	float mDamage; //이건 낙하데미지임 실상 바닥 충돌 순간의 중력가속

	RECT mhitBox;
	

	Player* mPlayer;
	vector <Map*> mMapList;
	vector <Enemy*> mEnemyList;

public:

	inline float const GetG() { return mGravity; }
	inline void SetG(float newGravity) { mGravity = newGravity; }

	inline float const GetDamage() { return mDamage; }
	
	void PhysicsUpdate(); //중력 가속 계산 Gravity accelaration 
	void IsonthePlatform(); //모든 맵 오브젝트 충돌 판정 Map object collision
	void IstheHit(); //플레이어 피격 판정 Player hit

	void WitchCatHit(); //위치캣 피격 판정 WitchCat hit
	void EraseQ(); // 몹에 맞은 Q스킬 투사체 관리 Q projectile hit manager

	void DefenseW(); //W스킬로 예티 블루쉘 막기 W Yeit's blushell defender

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	void SetMap(vector <Map*> mapPtrList);
	void SetEnemy(vector <Enemy*> enemyPtrList);

	RECT GethitBox();


};

