#ifndef __ENT_ENEMY_H__
#define __ENT_ENEMY_H__

#include "EntMobile.h"

class j1Player;
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
	int		damage = 5;
	bool attacking;
	//NOTE: in the future it will be an entity
	j1Player* enemy;

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


};
#endif