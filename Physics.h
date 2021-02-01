#pragma once

class Player;
class Projectile;
class Map;
class Enemy;

class Physics
{
	Singleton(Physics)

	float mGravity;

	Player* mPlayer;
	vector <Map*> mMapList;
	vector <Enemy*> mEnemyList;

public:

	float GetG() { return mGravity; }
	void SetG(float newGravity) { mGravity = newGravity; }
	
	void PhysicsUpdate(); //중력 가속 계산
	void IsonthePlatform(); //모든 맵 오브젝트 충돌 판정
	void IstheHit(); //플레이어 피격 판정

	void WitchCatHit(); //위치캣 피격 판정
	void EraseQ(); // 몹에 맞은 Q스킬 투사체 관리

	void DefenseW(); //W스킬로 예티 블루쉘 막기

	inline void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	void SetMap(vector <Map*> mapPtrList);
	void SetEnemy(vector <Enemy*> enemyPtrList);


};

