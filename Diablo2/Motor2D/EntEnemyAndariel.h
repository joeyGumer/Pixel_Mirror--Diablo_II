#ifndef __ENT_ENEMY_ANDARIEL_H__
#define __ENT_ENEMY_ANDARIEL_H__

#include "EntEnemy.h"
#include "j1ParticleManager.h"

class EntEnemyAndariel : public EntEnemy
{
public:

	//Constructor
	EntEnemyAndariel(const iPoint &p, uint ID, int lvl);

	bool Update(float dt);

	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

	void SetAnimations();
	void SetParticles();

	void CheckToCast();
	void UpdateRangedAttack();
	bool PlayerInCastRange();
	bool ReadyToCast();

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

	int row_number;

	j1Timer win;

	bool portal_appeared = false;
};

#endif