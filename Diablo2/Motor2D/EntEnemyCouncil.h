#ifndef __ENT_ENEMY_COUNCIL_H__
#define __ENT_ENEMY_COUNCIL_H__


#include "EntEnemy.h"
#include "j1ParticleManager.h"

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
	void SetParticles();

	bool ReadyToCast();
	void UpdateCast();
	bool PlayerInCastRange();


public:
	uint last_update;

	//Particles
	Particle	particle;
	fPoint		particle_destination;
	bool		particle_is_casted = false;

	int magic_damage;
	float magic_range;
	int magic_cooldown;
	j1Timer magic_timer;

	SDL_Texture*		cast_tex;
	vector<Animation>	cast;

};

#endif