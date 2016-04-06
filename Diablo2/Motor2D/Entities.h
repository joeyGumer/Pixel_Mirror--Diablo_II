#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "SDL\include\SDL.h"
#include "p2Point.h"
#include "Animation.h"

//NOTE: the copy paste is strong in this one,
//at least adapt it at the same style as our code :3
//and make a .h for declaration and a .cpp for definition (Carlos does it this way because he doesn't want to go from .h to .cpp)
//like this is just a mess
//and of course, becouse of the includes up there

//NOTE: got AIDS with this, at least the animation sprite_sheet is ready at the data.zip
enum ENTITY_TYPE
{
	ENEMY_DEBUG,
};

class Entity
{

public:

	//Constructors
	Entity(const iPoint &p, uint ID);

	//Destructor
	~Entity();

	//Draw
	void Draw();

	//Debug Draw
	void DrawDebug();

	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	iPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;

	//Setters
	virtual void SetAnimations() {}

//Attributes
public:
	SDL_Rect		rect;
	ENTITY_TYPE		type;
	iPoint			pivot;
	iPoint			tile_pos;
	uint			id;

	Animation		current_animation;
	SDL_Texture*	sprite;
	SDL_Texture*    idle;
	Animation		idle_front;
	

};

class entEnemyDebug : public Entity
{
public:

	entEnemyDebug(iPoint &position, uint id);

	void SetAnimations();

private:

};

#endif