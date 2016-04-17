#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "SDL\include\SDL.h"
#include "p2Point.h"
#include "Animation.h"

struct Sprite;

enum ENTITY_TYPE
{
	ENEMY,
	ENEMY_CRAWLER,
	ENEMY_BOSS,
	NPC,
	PROP,
	ITEM,
	ITEM_HEALTH,
};

class Entity
{

public:

	//Constructors
	Entity(const iPoint &p, uint ID);

	//Destructor
	~Entity();

	//Update
	virtual bool Update(float dt) { return true; }

	//Draw
	virtual void Draw() {};

	//Debug Draw
	virtual void DrawDebug() {};

	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	fPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;

	
public:

	//Attributes
	SDL_Rect		collider_rect;
	SDL_Rect		sprite_rect;
	iPoint			sprite_dim;
	ENTITY_TYPE		type;
	iPoint			pivot;
	iPoint			sprite_pivot;
	fPoint			position;
	uint			id;

	Sprite*			sprite;

	SDL_Texture*	tex;

};

#endif