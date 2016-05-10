#ifndef __ENT_ENEMY_SHAMAN_H__
#define __ENT_ENEMY_SHAMAN_H__

#include "EntEnemy.h"

class EntEnemyShaman : public EntEnemy
{
public:

	//Constructor
	EntEnemyShaman(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;

};

#endif