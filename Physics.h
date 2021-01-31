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
	vector <Projectile*> mProjectileList;
	vector <Enemy*> mEnemyList;

public:

	Physics();

	float GetG() { return mGravity; }
	void SetG(float newGravity) { mGravity = newGravity; }
	
	void PhysicsUpdate();
	void IsonthePlatform();
	void IstheHit();

	inline void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	void SetMap(vector <Map*> mapPtrList);
	void SetEnemy(vector <Enemy*> enemyPtrList);


};

