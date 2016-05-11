#ifndef __ENT_ENEMY_SUMMONER_H__
#define __ENT_ENEMY_SUMMONER_H__

#include "EntEnemy.h"
#include "j1ParticleManager.h"

class EntEnemySummoner : public EntEnemy
{
public:

	//Constructor
	EntEnemySummoner(const iPoint &p, uint ID);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();
	void SetParticles();

	void CheckToCast();
	void UpdateRangedAttack();

public:
	uint last_update;

	//Particles
	Particle	particle_summoner;
	fPoint		particle_destination;
	bool		particle_is_casted = false;
};

#endif