#include "Entities.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Player.h"
#include "j1Game.h"

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
	movement = false;
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
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();
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

	//Agro Draw
	SDL_Rect agro_rect;
	agro_rect.x = GetPlayerRect().x - target_radius;
	agro_rect.w = GetPlayerRect().w + target_radius*2;
	agro_rect.y = GetPlayerRect().y - target_radius;
	agro_rect.h = GetPlayerRect().h + target_radius*2;

	App->render->DrawQuad(agro_rect, 0, 0, 255, 1000, false);

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

//Movement
void Entity::SetInitVelocity()
{
	target = App->game->player->GetMapPosition();

	velocity.x = target.x - rect.x;
	velocity.y = target.y - rect.y;

	velocity.SetModule(PLAYER_SPEED);

}

void Entity::Move(float dt)
{
	fPoint vel = velocity * dt;

	rect.x += int(vel.x);
	rect.y += int(vel.y);
}

void Entity::UpdateVelocity(float dt)
{
	velocity.x = target.x - rect.x;
	velocity.y = target.y - rect.y;

	velocity.SetModule(PLAYER_SPEED * 0.75f);

	SetDirection();
}

bool Entity::IsTargetReached()
{
	fPoint vel;

	vel.x = target.x - rect.x;
	vel.y = target.y - rect.y;

	if (vel.GetModule() <= target_radius)
	{
		if (!path_on)
		{
			current_input = ENTITY_INPUT_STOP_MOVE;
			movement = false;
		}

		return true;
	}

	return false;
}

void Entity::SetTarget(iPoint _target)
{
	target = _target;
	movement = true;
	target_reached = false;
}

void Entity::GetNewTarget()
{
	if ((uint)current_node + 1< path.size())
	{
		current_node++;
		SetTarget(App->map->GetTileCenter(path[current_node].x, path[current_node].y));
	}
	else
	{
		current_input = ENTITY_INPUT_STOP_MOVE;
		movement = false;
	}
}

void Entity::UpdateMovement(float dt)
{
	if (movement)
	{
		if (!target_reached)
		{
			UpdateVelocity(dt);
			Move(dt);
			if (IsTargetReached())
				target_reached = true;
		}
		else
		{
			GetNewTarget();
		}
	}
}

void Entity::SetMovement(int x, int y)
{
	if (path_on)
	{
		SetNewPath(x, y);
	}
	else
	{
		iPoint target = App->map->GetTileCenter(x, y);
		SetTarget(target);

		//StateMachine change
		current_input = ENTITY_INPUT_MOVE;
	}
}

void Entity::SetNewPath(int x, int y)
{
	iPoint start = App->map->WorldToMap(rect.x, rect.y);
	iPoint goal = { x, y };

	int steps = App->pathfinding->GetNewPath(start, goal, path);

	if (steps > 0)
	{
		//StateMachine change
		current_input = ENTITY_INPUT_MOVE;

		movement = true;
		current_node = -1;
		GetNewTarget();
	}

}

void Entity::SetDirection()
{
	float angle = velocity.GetAngle();

	ENTITY_DIRECTION dir;

	if (angle < 22.5 && angle > -22.5)
		dir = ENTITY_D_RIGHT;
	else if (angle >= 22.5 && angle <= 67.5)
		dir = ENTITY_D_FRONT_RIGHT;
	else if (angle > 67.5 && angle < 112.5)
		dir = ENTITY_D_FRONT;
	else if (angle >= 112.5 && angle <= 157.5)
		dir = ENTITY_D_FRONT_LEFT;
	else if (angle > 157.5 || angle < -157.5)
		dir = ENTITY_D_LEFT;
	else if (angle >= -157.5 && angle <= -112.5)
		dir = ENTITY_D_BACK_LEFT;
	else if (angle > -112.5 && angle < -67.5)
		dir = ENTITY_D_BACK;
	else if (angle >= -67.5 && angle <= -22.5)
		dir = ENTITY_D_BACK_RIGHT;

	if (dir != current_direction)
	{
		current_direction = dir;
		current_animation = &current_animation_set[current_direction];
	}
}

//---------------------------------------


//DebugEnemy Code
//---------------------------------------

//Constructor
entEnemyDebug::entEnemyDebug(iPoint &position, uint id) : Entity(position, id)
{
	SetAnimations();
	pivot = { (rect.w / 2), (rect.h - 5) };
	type = ENEMY_DEBUG;
	current_action = ENTITY_IDLE;
	current_input = ENTITY_INPUT_NULL;
	current_direction = ENTITY_D_FRONT;
	current_animation_set = idle_set;
	current_animation = &current_animation_set[current_direction];
}

bool entEnemyDebug::Update(float dt)
{
	UpdateAction();

	fPoint player_rect = App->game->player->GetPivotPosition();

	if (player_rect.x >= GetPlayerRect().x - target_radius &&
		player_rect.x <= GetPlayerRect().x + GetPlayerRect().w + target_radius*2 &&
		player_rect.y >= GetPlayerRect().y - target_radius &&
		player_rect.y <= GetPlayerRect().y + GetPlayerRect().h + target_radius*2)
	{
		int targetX = player_rect.x;
		int targetY = player_rect.y;
		iPoint _target = { targetX, targetY };
		_target = App->map->WorldToMap(_target.x, _target.y);
		SetMovement(_target.x, _target.y);
	}

	UpdateMovement(dt);

	return true;
}

//Animation Setter
void entEnemyDebug::SetAnimations()
{
	sprite = idle = App->tex->Load("textures/wolf.png");
	walk = App->tex->Load("textures/wolf_walk.png");
	rect.w = 69;
	rect.h = 54;

	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (54 + 1) * i, 69, 54, 12, 1);
		tmp.speed = 0.2f;

		idle_set.push_back(tmp);
	}

	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (73 + 1) * i, 94, 73, 12, 1);
		tmp.speed = 0.2f;

		walk_set.push_back(tmp);
	}

}

ENTITY_STATE entEnemyDebug::UpdateAction()
{
	if (current_input != ENTITY_INPUT_NULL && current_input != previous_input)
	{
		switch (current_action)
		{
		case ENTITY_IDLE:
		{
			if (current_input == ENTITY_INPUT_MOVE)
			{
				current_action = ENTITY_WALKING;
			}
		}
		break;

		case ENTITY_WALKING:
		{
			if (current_input == ENTITY_INPUT_STOP_MOVE)
			{
				current_action = ENTITY_IDLE;
			}
		}
		break;

		case ENTITY_ATTACKING:
		{

		}
		break;
		}

		previous_input = current_input;
		EntityEvent(ENTITY_STATE_CHANGE);
	}

	current_input = ENTITY_INPUT_NULL;
	return current_action;
}

void entEnemyDebug::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
		case ENTITY_STATE_CHANGE:
		{
			StateMachine();
		}
	}
}

void entEnemyDebug::StateMachine()
{
	switch (current_action)
	{
	case ENTITY_IDLE:
		sprite = idle;
		current_animation_set = idle_set;
		//current_animation = idle_front;
		rect.w = 69;
		rect.h = 54;
		pivot = { (rect.w / 2), (rect.h - 5) };
		break;
	case ENTITY_WALKING:
		sprite = walk;
		current_animation_set = walk_set;
		//current_animation = walk_front;
		rect.w = 94;
		rect.h = 73;
		pivot = { (rect.w / 2), (rect.h - 5) };
		break;
	case ATTACKING:
		break;
	}
}
//---------------------------------------

//DebugEnemy Code
//---------------------------------------

//Constructor
entEnemyCrawler::entEnemyCrawler(iPoint &position, uint id) : Entity(position, id)
{
	SetAnimations();
	pivot = { (rect.w / 2), (rect.h - 5) };
	type = ENEMY_CRAWLER;
	current_action = ENTITY_IDLE;
	current_input = ENTITY_INPUT_NULL;
	current_direction = ENTITY_D_FRONT;
	current_animation_set = idle_set;
	current_animation = &current_animation_set[current_direction];
}

bool entEnemyCrawler::Update(float dt)
{
	UpdateAction();

	fPoint player_rect = App->game->player->GetPivotPosition();

	if (player_rect.x >= GetPlayerRect().x - target_radius &&
		player_rect.x <= GetPlayerRect().x + GetPlayerRect().w + target_radius * 2 &&
		player_rect.y >= GetPlayerRect().y - target_radius &&
		player_rect.y <= GetPlayerRect().y + GetPlayerRect().h + target_radius * 2)
	{
		int targetX = player_rect.x;
		int targetY = player_rect.y;
		iPoint _target = { targetX, targetY };
		_target = App->map->WorldToMap(_target.x, _target.y);
		SetMovement(_target.x, _target.y);
	}

	UpdateMovement(dt);

	return true;
}

//Animation Setter
void entEnemyCrawler::SetAnimations()
{
	sprite = idle = App->tex->Load("textures/crawler_idle.png");
	walk = App->tex->Load("textures/crawler_walk.png");
	rect.w = 78;
	rect.h = 51;

	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (51 + 0) * i, 78, 51, 4, 0);
		tmp.speed = 0.2f;

		idle_set.push_back(tmp);
	}

	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (54 + 0) * i, 78, 54, 9, 0);
		tmp.speed = 0.2f;

		walk_set.push_back(tmp);
	}

}

ENTITY_STATE entEnemyCrawler::UpdateAction()
{
	if (current_input != ENTITY_INPUT_NULL && current_input != previous_input)
	{
		switch (current_action)
		{
		case ENTITY_IDLE:
		{
			if (current_input == ENTITY_INPUT_MOVE)
			{
				current_action = ENTITY_WALKING;
			}
		}
		break;

		case ENTITY_WALKING:
		{
			if (current_input == ENTITY_INPUT_STOP_MOVE)
			{
				current_action = ENTITY_IDLE;
			}
		}
		break;

		case ENTITY_ATTACKING:
		{

		}
		break;
		}

		previous_input = current_input;
		EntityEvent(ENTITY_STATE_CHANGE);
	}

	current_input = ENTITY_INPUT_NULL;
	return current_action;
}

void entEnemyCrawler::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void entEnemyCrawler::StateMachine()
{
	switch (current_action)
	{
	case ENTITY_IDLE:
		sprite = idle;
		current_animation_set = idle_set;
		//current_animation = idle_front;
		rect.w = 78;
		rect.h = 51;
		pivot = { (rect.w / 2), (rect.h - 5) };
		break;
	case ENTITY_WALKING:
		sprite = walk;
		current_animation_set = walk_set;
		//current_animation = walk_front;
		rect.w = 78;
		rect.h = 54;
		pivot = { (rect.w / 2), (rect.h - 5) };
		break;
	case ATTACKING:
		break;
	}
}