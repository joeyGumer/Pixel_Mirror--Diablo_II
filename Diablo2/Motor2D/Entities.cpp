#include "Entities.h"

//Entity Code
//---------------------------------------

//Constructor
Entity::Entity(const iPoint &p, uint ID)
{
	//NOTE: wow, this will need to be adapted well, look how it's done with the player (i refer to the map - world conversion, and positioning through a pivot)
	iPoint tmp = App->map->WorldToMap(p.x, p.y);
	tile_pos = tmp;
	tmp = App->map->MapToWorld(tmp.x, tmp.y);
	dim.x = tmp.x;
	dim.y = tmp.y;
	id = ID;
}

//Destructor
Entity::~Entity()
{
	SDL_DestroyTexture(idle);
}

void Entity::Draw()
{
	App->render->Blit(idle, dim.x, dim.y);
}

//---------------------------------------


//DebugEnemy Code
//---------------------------------------

//Constructor
entEnemyDebug::entEnemyDebug(iPoint &p, uint id) : Entity(p, id)
{
	idle = App->tex->Load("textures/enemy1.png");
	SDL_QueryTexture(idle, NULL, NULL, &dim.w, &dim.h);

	type = ENEMY_DEBUG;
}

//---------------------------------------
