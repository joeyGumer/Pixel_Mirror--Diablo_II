#include "Entities.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"

//Entity Code
//---------------------------------------

//Constructor
Entity::Entity(const iPoint &p, uint ID)
{
	//NOTE: wow, this will need to be adapted well, look how it's done with the player (i refer to the map - world conversion, and positioning through a pivot)
	iPoint tmp = App->map->WorldToMap(p.x, p.y);
	tile_pos = tmp;
	tmp = App->map->MapToWorld(tmp.x, tmp.y);
	rect.x = tmp.x - (App->map->data.tile_width / 2);
	rect.y = tmp.y;
	id = ID;
}

//Destructor
Entity::~Entity()
{
	SDL_DestroyTexture(sprite);
	SDL_DestroyTexture(idle);
}

void Entity::Draw()
{
	iPoint pos = GetBlitPosition();
	SDL_Rect current_sprite = current_animation.GetCurrentFrame();
	App->render->Blit(sprite, pos.x, pos.y, &current_sprite);
}

void Entity::DrawDebug()
{
	//iPoint t_pos = tile_pos;
	iPoint p_pos = GetPivotPosition();

	//App->render->Blit(p_debug, t_pos.x, t_pos.y);
	App->render->DrawQuad(GetPlayerRect(), 255, 0, 0, 1000, false);
	//App->render->DrawCircle(p_pos.x, p_pos.y, 5, 255, 0, 0, 1000);
	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0);

}

//Getters
iPoint Entity::GetMapPosition() const
{
	return App->map->WorldToMap(rect.x, rect.y);
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
	iPoint ret = GetPivotPosition();
	ret.x -= pivot.x;
	ret.y -= pivot.y;

	return  ret;
}

iPoint Entity::GetPivotPosition() const
{
	//NOTE : put a tile pivot?, more accesible
	iPoint ret = { rect.x, rect.y };
	return ret;
}

SDL_Rect Entity::GetPlayerRect() const
{
	//NOTE: this may be adapted when we use colliders
	iPoint pos = GetBlitPosition();

	return{ pos.x, pos.y, rect.w, rect.h };
}

//---------------------------------------


//DebugEnemy Code
//---------------------------------------

//Constructor
entEnemyDebug::entEnemyDebug(iPoint &position, uint id) : Entity(position, id)
{
	SetAnimations();
	current_animation = idle_front;
	pivot = { (rect.w / 2), (rect.h - 5) };
	type = ENEMY_DEBUG;
}

//Animation Setter
void entEnemyDebug::SetAnimations()
{
	sprite = idle = App->tex->Load("textures/wolf.png");
	rect.w = 69;
	rect.h = 54;
	idle_front.SetFrames(0, 0, rect.w, rect.h, 12, 1);
	idle_front.speed = 0.2f;
}
//---------------------------------------
