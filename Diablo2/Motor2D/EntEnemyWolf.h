#ifndef __ENT_ENEMY_WOLF_H__
#define __ENT_ENEMY_WOLF_H__

#include "EntEnemy.h"

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