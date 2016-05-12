#ifndef __ENT_ENEMY_NEST_H__
#define __ENT_ENEMY_NEST_H__

#include "EntEnemy.h"
#include "j1ParticleManager.h"

class EntEnemyNest : public EntEnemy
{
public:

	//Constructor
	EntEnemyNest(const iPoint &p, uint ID);
	~EntEnemyNest();

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();
	void SetParticles();

	void CheckToCast();
	void UpdateRangedAttack();

	bool PlayerInSummonRange();
	bool ReadyToSummon();
	void UpdateSummon();

public:
	uint last_update;

	//Particles
	fPoint		particle_destination;
	bool		particle_is_casted = false;
	int			particle_speed;

	float summon_range;
	int summon_cooldown;
	j1Timer summon_timer;
	list<Entity*> summon_list;
	bool summoned = false;
};

#endif
