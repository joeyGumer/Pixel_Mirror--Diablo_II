#ifndef __ENT_ENEMY_H__
#define __ENT_ENEMY_H__

#include "EntMobile.h"
#include "j1Timer.h"

enum ENEMY_TYPE
{
	ENEMY_WOLF,
	ENEMY_CRAWLER,
	ENEMY_COUNCIL,
	ENEMY_SUMMONER,
	ENEMY_SHAMAN,
	ENEMY_IZUAL,
};

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

	//Item droping Algorithm
	void DropItem(iPoint pos);

	
public:

	//Attributes

	//Health
	int		HP_max;
	int		HP_current;

	//Attack
	float	attack_range;
	bool	attacking = false;
	//NOTE: in the future it will be an entity
	j1Player* enemy;

	//Detection
	float	agro_range;

	ENEMY_TYPE enemy_type;
	int		damage;

	//Pure Blood System;
	int		blood_drop;

	const char*  name;

	//HP bar
	float   total_width;
	float   xpos;

};

#endif