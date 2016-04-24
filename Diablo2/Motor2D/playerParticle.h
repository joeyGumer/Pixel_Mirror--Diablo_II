#ifndef __PLAYER_PARTICLE_H__
#define __PLAYER_PARTICLE_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"

class playerParticle
{
public:
	playerParticle();
	playerParticle(fPoint init, fPoint end);
	~playerParticle();

	bool Update(float dt);
	void Draw();

	void SetInitVelocity();

public:
	//NOTE: Most of them are debug attributes
	SDL_Rect particle_rect;

	fPoint	destination;

	fPoint	velocity;
	float	speed;

};

#endif