#pragma once

class Player;
class Projectile;
class Map;
class Enemy;

class Physics
{
	Singleton(Physics)

	float mGravity;
	float mDamage;

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


};

