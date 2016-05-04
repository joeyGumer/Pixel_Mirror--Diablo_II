#ifndef __ENT_ENEMY_H__
#define __ENT_ENEMY_H__

#include "EntMobile.h"
#include "j1Timer.h"

/*enum ENEMY_TYPE
{
	ENEMY_WOLF,
	ENEMY_CRAWLER,
	ENEMY_BOSS,
};*/

class j1Player;

#define PATHFINDING_FRAMES 60


class EntEnemy : public EntMobile
{
public:

	//Constructor
	EntEnemy(const iPoint &p, uint ID);

	//Drawing methods
	void Draw();
	void DrawDebug();

	bool PlayerInRange();
	bool PlayerInAttackRange();

	//Damage
	void TakeDamage(int damage);
	void DrawHPbar();
	
	//Attack
	void UpdateAttack();
	void CheckToAttack();

	
public:

	//Attributes

	//Health
	int		HP_max;
	int		HP_current;

	//Attack
	float	attack_range;
	bool attacking;
	//NOTE: in the future it will be an entity
	j1Player* enemy;

	//Detection
	float	agro_range;

	//ENEMY_TYPE emy_type;
	int		damage;

	//Pure Blood System;
	int		blood_drop;

	const char*  name;

};


class EntEnemyWolf : public EntEnemy
{
public:

	//Constructor
	EntEnemyWolf(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;

};


class EntEnemyCrawler : public EntEnemy
{
public:

	//Constructor
	EntEnemyCrawler(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;
	
};


class EntEnemyBoss : public EntEnemy
{
public:

	//Constructor
	EntEnemyBoss(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;
	j1Timer win;
	
};
#endif