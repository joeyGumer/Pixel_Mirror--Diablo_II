#ifndef __ENT_ENEMY_H__
#define __ENT_ENEMY_H__

#include "EntMobile.h"

#define PATHFINDING_FRAMES 10

class EntEnemy : public EntMobile
{
public:

	//Constructor
	EntEnemy(const iPoint &p, uint ID);

	//Drawing methods
	void Draw();
	void DrawDebug();

	bool PlayerInRange();

	//Damage
	void TakeDamage(int damage);
	void DrawHPbar();

public:

	//Attributes

	//Health
	int		HP_max;
	int		HP_current;

	//Attack
	float	attack_range = 100.0f;

	//Detection
	float	agro_range;
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
#endif