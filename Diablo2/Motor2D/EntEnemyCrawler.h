#ifndef __ENT_ENEMY_CRAWLER_H__
#define __ENT_ENEMY_CRAWLER_H__

#include "EntEnemy.h"

class EntEnemyCrawler : public EntEnemy
{
public:

	//Constructor
	EntEnemyCrawler(const iPoint &p, uint ID, int lvl);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();

public:
	uint last_update;

};

#endif