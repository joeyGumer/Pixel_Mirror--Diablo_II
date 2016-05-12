#ifndef __ENT_ENEMY_IZUAL_H__
#define __ENT_ENEMY_IZUAL_H__

#include "EntEnemy.h"
#include "j1ParticleManager.h"

class EntEnemyIzual : public EntEnemy
{
public:

	//Constructor
	EntEnemyIzual(const iPoint &p, uint ID, int lvl);

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
	Particle	particle_izual;
	fPoint		particle_destination;
	bool		particle_is_casted = false;

	int magic_damage;
	float magic_range;
	int magic_cooldown;
	j1Timer magic_timer;

	SDL_Texture*		cast_tex;
	vector<Animation>	cast;


	j1Timer win;
};

#endif