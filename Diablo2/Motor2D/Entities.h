#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "SDL\include\SDL.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1App.h"
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

	SDL_Rect		dim;
	ENTITY_TYPE		type;
	uint			id;
	iPoint			tile_pos;
	
	//Animations
	SDL_Rect		current_sprite;
	SDL_Texture*    idle;
	Animation		idle_front;

	//Constructors
	Entity(const iPoint &p, uint ID);

	//Destructor
	~Entity();

	//Draw
	void Draw();

};

class entEnemyDebug : public Entity
{
public:

	entEnemyDebug(iPoint &p, uint id);

};

#endif