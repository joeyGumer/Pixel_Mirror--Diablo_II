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
class Emisor;
class FireEmisor;
class BurstEmisor;
class Collider;

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
	bool CleanActiveEmisors();

	Particle* AddParticle(const Particle& p, int x, int y, Uint32 secLife = INT_MAX, SDL_Texture* texture = NULL,
		unsigned int sfx = 0, uint32 delay = 0);

	Emisor* AddEmisor(Particle& p, int x, int y, float emisorDuration, Uint32 particleLife, int particleVelocity, float minAngle = 0.0f, float maxAngle = 360.0f,
		SDL_Texture* tex = NULL);

	FireEmisor* AddFire(int x, int y, float duration);
	BurstEmisor* AddBurst(int x, int y);

private:
	SDL_Texture* texture;
	std::string textureFile;

	//TODO 1: Create two list, one with particles and another one with emisors. Call the particle list "particleList" and the emisor list "emisorList"
	std::list<Particle*> particleList;
	std::list<Emisor*> emisorList;

	bool LoadParticlesFile(pugi::xml_document& file);

public:
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
	fPoint				collider_margin;

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


class Emisor
{
public:
	fPoint		position;
	fPoint		speed;
	float		duration;
	j1Timer*	timer;
	bool		active;
	bool		alive;
	uint	    fx;
	bool		fxPlayed;
	Particle    particleEmited;
	float	    velocity;
	float		minAngle;
	float		maxAngle;

public:
	Emisor();
	Emisor(Particle& p);
	virtual ~Emisor();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	void SetParticle(Particle& particle);
	void Enable();
	void Disable();
	void Destroy();
};

class FireEmisor : public Emisor
{
public:
	Particle	fire;
	Particle	smoke;


	float		smokeFrequence;
	float		smokeStart;
	bool	    fireStarted = false;
	iPoint		smokeOffset;


public:
	FireEmisor(float time);
	~FireEmisor();

	bool Update(float dt);
	bool PostUpdate();

private:
	float	   acumulator = 0.0f;
};

class BurstEmisor : public Emisor
{
public:
	Particle	burst;
	Emisor		emisor_burst;
	bool	    burstStarted = false;

public:
	BurstEmisor();
	~BurstEmisor();

	bool Update(float dt);
	bool PostUpdate();

};

#endif