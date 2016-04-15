#include "Entity.h"
#include "j1App.h"
#include "j1Map.h"

//Constructor
Entity::Entity(const iPoint &p, uint ID)
{
	iPoint tmp = App->map->WorldToMap(p.x, p.y);
	//position.x = tmp.x;
	//position.y = tmp.y;
	tmp = App->map->MapToWorld(tmp.x, tmp.y);
	position.x = tmp.x - (App->map->data.tile_width / 2);
	position.y = tmp.y;
	id = ID;
}

//Destructor
Entity::~Entity()
{
	SDL_DestroyTexture(sprite);
}

//Getters
iPoint Entity::GetMapPosition() const
{
	return App->map->WorldToMap(position.x, position.y);
}

iPoint Entity::GetTilePosition() const
{
	iPoint ret = GetMapPosition();
	ret = App->map->MapToWorld(ret.x, ret.y);
	ret.x -= App->map->data.tile_width / 2;
	return ret;
}

iPoint Entity::GetBlitPosition() const
{
	fPoint tmp = GetPivotPosition();
	iPoint ret(tmp.x, tmp.y);
	ret.x -= pivot.x;
	ret.y -= pivot.y;

	return ret;
}

fPoint Entity::GetPivotPosition() const
{
	//NOTE : put a tile pivot?, more accesible
	return position;
}

SDL_Rect Entity::GetPlayerRect() const
{
	//NOTE: this may be adapted when we use colliders
	iPoint pos = GetBlitPosition();

	return{ pos.x, pos.y, sprite_dim.x, sprite_dim.y };
}