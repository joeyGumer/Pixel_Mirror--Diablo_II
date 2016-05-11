#ifndef __ENT_ENEMY_COUNCIL_H__
#define __ENT_ENEMY_COUNCIL_H__


#include "EntEnemy.h"

class EntEnemyCouncil : public EntEnemy
{
public:

	//Constructor
	EntEnemyCouncil(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;

	int magic_damage;
	float magic_range;
	int magic_cooldown;

};

#endif