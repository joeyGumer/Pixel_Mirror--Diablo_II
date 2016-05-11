#ifndef __ENT_ENEMY_SHAMAN_H__
#define __ENT_ENEMY_SHAMAN_H__

#include "EntEnemy.h"
#include "j1ParticleManager.h"

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
	void SetParticles();

	void CheckToCast();
	void UpdateRangedAttack();

public:
	uint last_update;

	//Particles
	Particle	particle_shaman;
	fPoint		particle_destination;
	bool		particle_is_casted = false;
	int			particle_speed;

	int heal_effect;
	float heal_range;
	int heal_cooldown;
};

#endif