#include "EntMobile.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "j1Collision.h"

//Constructor
EntMobile::EntMobile(const iPoint &p, uint ID) : Entity(p, ID)
{
	current_action = ENTITY_IDLE;
	current_input = ENTITY_INPUT_NULL;
	current_direction = ENTITY_D_FRONT;
}

//Destructor
EntMobile::~EntMobile()
{
	SDL_DestroyTexture(idle_tex);
	SDL_DestroyTexture(walk_tex);
}

void EntMobile::SetDirection()
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

void EntMobile::SetDirection(fPoint pos)
{
	fPoint direction;
	direction.x = pos.x - position.x;
	direction.y = pos.y - position.y;

	direction.SetModule(1);

	float angle = direction.GetAngle();

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

//Movement
//---------------------------
void EntMobile::SetInitVelocity()
{
	//NOTE: This only works when the target is the player, may be changed in other cases
	//		Maybe a SetInitVelocity(target) would solve this possible issue
	target = App->game->player->GetMapPosition();

	velocity.x = target.x - position.x;
	velocity.y = target.y - position.y;

	velocity.SetModule(speed);

}

void EntMobile::Move(float dt)
{
	fPoint vel = velocity * dt;

	position.x += int(vel.x);
	position.y += int(vel.y);

	collider->rect.x += int(vel.x);
	collider->rect.y += int(vel.y);
}

void EntMobile::UpdateVelocity(float dt)
{
	velocity.x = target.x - position.x;
	velocity.y = target.y - position.y;

	velocity.SetModule(speed);

	SetDirection();
}

bool EntMobile::IsTargetReached()
{
	fPoint vel;

	vel.x = target.x - position.x;
	vel.y = target.y - position.y;

	//NOTE: This may be modified to insert attack

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

void EntMobile::SetTarget(iPoint _target)
{
	target = _target;
	movement = true;
	target_reached = false;
}

void EntMobile::GetNewTarget()
{
	//NOTE: This may be modified to insert attack

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

iPoint EntMobile::FindClosestWalkable(iPoint pos)
{
	bool found = false;
	int lenght = 0;

	iPoint tile = { pos.x, pos.y };

	while (!found && lenght < 10)
	{
		while (tile.y < pos.y + lenght && !found)
		{
			tile.y++;
			if (App->pathfinding->IsWalkable(tile))
				found = true;
		}

		while (tile.x > pos.x - lenght && !found)
		{
			tile.x--;
			if (App->pathfinding->IsWalkable(tile))
				found = true;
		}

		while (tile.y > pos.y - lenght && !found)
		{
			tile.y--;
			if (App->pathfinding->IsWalkable(tile))
				found = true;

		}

		while (tile.x < pos.x + lenght && !found)
		{
			tile.x++;
			if (App->pathfinding->IsWalkable(tile))
				found = true;
		}
		lenght += 1;
	}
	return tile;
}

void EntMobile::UpdateMovement(float dt)
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

void EntMobile::SetMovement(int x, int y)
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

void EntMobile::SetNewPath(int x, int y)
{
	iPoint start = App->map->WorldToMap(position.x, position.y);
	iPoint goal = { x, y };

	if (App->game->em->EntityOnCoords(App->map->MapToWorld(GetMapPosition().x, GetMapPosition().y)) != NULL &&
		App->game->em->EntityOnCoords(App->map->MapToWorld(GetMapPosition().x, GetMapPosition().y)) != this)
	{
		goal = FindClosestWalkable(goal);
	}

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
//---------------------------