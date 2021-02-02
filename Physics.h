#pragma once

class Player;
class Projectile;
class Map;
class Enemy;

class Physics
{
	Singleton(Physics) //��� �浹ó���� Physics �̱����� ó���Ѵ�

	float mGravity;
	float mDamage; //�̰� ���ϵ������� �ǻ� �ٴ� �浹 ������ �߷°���

	RECT mhitBox;
	

	Player* mPlayer;
	vector <Map*> mMapList;
	vector <Enemy*> mEnemyList;

public:

	inline float const GetG() { return mGravity; }
	inline void SetG(float newGravity) { mGravity = newGravity; }

	inline float const GetDamage() { return mDamage; }
	
	void PhysicsUpdate(); //�߷� ���� ��� Gravity accelaration 
	void IsonthePlatform(); //��� �� ������Ʈ �浹 ���� Map object collision
	void IstheHit(); //�÷��̾� �ǰ� ���� Player hit

	void WitchCatHit(); //��ġĹ �ǰ� ���� WitchCat hit
	void EraseQ(); // ���� ���� Q��ų ����ü ���� Q projectile hit manager

	void DefenseW(); //W��ų�� ��Ƽ ��罩 ���� W Yeit's blushell defender

	void SetPlayer(Player* playerPtr) { mPlayer = playerPtr; }
	void SetMap(vector <Map*> mapPtrList);
	void SetEnemy(vector <Enemy*> enemyPtrList);

	RECT GethitBox();


};

