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
	
	void PhysicsUpdate(); //�߷� ���� ���
	void IsonthePlatform(); //��� �� ������Ʈ �浹 ����
	void IstheHit(); //�÷��̾� �ǰ� ����

	void WitchCatHit(); //��ġĹ �ǰ� ����
	void EraseQ(); // ���� ���� Q��ų ����ü ����

	void DefenseW(); //W��ų�� ��Ƽ ��罩 ����

	inline void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	void SetMap(vector <Map*> mapPtrList);
	void SetEnemy(vector <Enemy*> enemyPtrList);


};

