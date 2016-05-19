#ifndef __j1PARTICLE_MANAGER_H__
#define __j1PARTICLE_MANAGER_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include <list>
#include "j1FileSystem.h"
#include "j1Timer.h"

#define PI 3.14159265

struct SDL_Texture;
class Particle;
class Collider;

enum PARTICLE_TYPE
{
	PARTICLE_PLAYER_CAST,
	PARTICLE_ENEMY_CAST,
	PARTICLE_BUFF
};

class j1ParticleManager : public j1Module
{
public:
	j1ParticleManager();
	~j1ParticleManager();

	bool Awake(pugi::xml_node &node);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool CleanActiveParticles();

	Particle* AddParticle(const Particle& p, int x, int y, Uint32 secLife = INT_MAX, SDL_Texture* texture = NULL,
		unsigned int sfx = 0, uint32 delay = 0);

private:
	SDL_Texture* texture;
	std::string textureFile;

	bool LoadParticlesFile(pugi::xml_document& file);

public:
	std::list<Particle*> particleList;
	pugi::xml_document particle_file;

};

struct Particle
{
	Animation			anim;
	unsigned int		fx; //This is for audio
	fPoint				position;
	fPoint				initialPosition;
	fPoint				speed;
	Uint32				life;	// Time the particle life
	bool				fxPlayed;
	j1Timer				timer;
	SDL_Texture*		image = NULL;
	bool				alive;
	bool				active = true;
	bool			    on = false;
	Collider*			collider = NULL;
	iPoint				collider_margin;
	iPoint				collider_pivot;
	PARTICLE_TYPE		type;
	int					damage = 0;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update(float dt);
	bool PostUpdate();
	void FollowPoint(int x, int y);
	void DestroyParticle();
	void Enable();
	void Disable();

	void SetSpeed(float velocity, float minAngle = 0.0f, float maxAngle = 360.0f);
	void SetPointSpeed(float velocity, fPoint target);
};

#endif