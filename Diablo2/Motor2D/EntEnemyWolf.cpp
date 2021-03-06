#include "EntEnemyWolf.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"

//Constructor
EntEnemyWolf::EntEnemyWolf(const iPoint &p, uint ID, int lvl) : EntEnemy(p, ID)
{
	name = "wolf";

	level = lvl;

	tex = idle_tex = App->game->em->wolf_idle;
	walk_tex = App->game->em->wolf_walk;
	death_tex = App->game->em->wolf_death;
	attack_tex = App->game->em->wolf_attack;

	SetAnimations();
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_WOLF;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 11;
	HP_max = HP_current = 15;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			HP_max *= 2;
			HP_current *= 2;
			random_range *= 2;
		}
	}
	int random = rand() % random_range;
	HP_max += random;
	HP_current = HP_max;

	//Speed
	speed = 200.0f;

	//Melee Attack
	random_range = 5;
	damage = 2;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			damage *= 2;
			random_range *= 2;
		}
	}
	random = rand() % random_range;
	damage += random;

	//Melee Attack Range
	attack_range = 40.0f;

	//Agro Range
	agro_range = 275.0f;

	//Pure Blood Drop
	blood_drop = 150;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			blood_drop += blood_drop / 2;
		}
	}
	//------------------------------------

	last_update = PATHFINDING_FRAMES;

	SDL_Rect col_rect;

	col_margin.x = 10;
	col_margin.y = 10;

	col_pivot.x = 0;
	col_pivot.y = 0;

	col_rect.x = GetPlayerRect().x + col_margin.x + col_pivot.x;
	col_rect.y = GetPlayerRect().y + col_margin.y + col_pivot.y;
	col_rect.w = GetPlayerRect().w - col_margin.x*2;
	col_rect.h = GetPlayerRect().h - col_margin.y*2;

	collider = App->collision->AddCollider(col_rect, COLLIDER_ENEMY, App->game->em);

	//Sprite creation
	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();
	sprite = new Sprite(tex, pos, sprite_pivot, current_sprite);
	App->render->AddSpriteToList(sprite);

}

//Update
bool EntEnemyWolf::Update(float dt)
{
	if (!dead)
	{
		if (frozen)
		{
			if (freeze_timer.ReadSec() >= freeze_time)
			{
				frozen = false;

				/*
				SDL_SetTextureColorMod(idle_tex,
					255,
					255,
					255);

				SDL_SetTextureColorMod(walk_tex,
					255,
					255,
					255);

				SDL_SetTextureColorMod(attack_tex,
					255,
					255,
					255);
					*/

				tex_frozen = false;
			}
			else
			{
				//TESTING SHITS
				//--------------
				/*
				if (!tex_frozen)
				{
					SDL_SetTextureColorMod(idle_tex,
						150,
						150,
						255);

					SDL_SetTextureColorMod(walk_tex,
						150,
						150,
						255);

					SDL_SetTextureColorMod(attack_tex,
						150,
						150,
						255);

					tex_frozen = true;
				}
				*/
				//--------------

				dt = dt / 2;
			}
		}

		UpdateAction();

		fPoint player_pos = App->game->player->GetPivotPosition();

		//NOTE: The enemy is for following the player one it has been founded, but for now, better not, because of the low framerate
		if ((PlayerInRange() /*|| enemy*/) && !attacking && last_update >= PATHFINDING_FRAMES)
		{
			last_update = 0;
			int target_x = player_pos.x;
			int target_y = player_pos.y;

			iPoint _target = { target_x, target_y };
			_target = App->map->WorldToMap(_target.x, _target.y);
			SetMovement(_target.x, _target.y);


			enemy = App->game->player;
		}

		if (App->game->em->EntityOnCoords(App->map->MapToWorld(GetMapPosition().x, GetMapPosition().y)) != NULL &&
			App->game->em->EntityOnCoords(App->map->MapToWorld(GetMapPosition().x, GetMapPosition().y)) != this &&
			last_update >= PATHFINDING_FRAMES &&
			movement == false)
		{
			int target_x = FindClosestWalkable(GetMapPosition()).x;
			int target_y = FindClosestWalkable(GetMapPosition()).y;

			iPoint _target = { target_x, target_y };
			_target = App->map->WorldToMap(_target.x, _target.y);
			SetMovement(_target.x, _target.y);

		}

		CheckToAttack();

		switch (current_action)
		{
		case ENTITY_ATTACKING:
			UpdateAttack();
		case ENTITY_WALKING:
			UpdateMovement(dt);
		}

		last_update++;
	}

	return true;
}

ENTITY_STATE EntEnemyWolf::UpdateAction()
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
			if (current_input == ENTITY_INPUT_DEATH)
			{
				current_action = ENTITY_DEATH;
			}
			if (current_input == ENTITY_INPUT_ATTACK)
			{
				current_action = ENTITY_ATTACKING;
			}
		}
		break;

		case ENTITY_WALKING:
		{
			if (current_input == ENTITY_INPUT_STOP_MOVE)
			{
				current_action = ENTITY_IDLE;
			}
			if (current_input == ENTITY_INPUT_DEATH)
			{
				current_action = ENTITY_DEATH;
			}
			if (current_input == ENTITY_INPUT_ATTACK)
			{
				current_action = ENTITY_ATTACKING;
			}
		}
		break;

		case ENTITY_ATTACKING:
		{
			if (current_input == ENTITY_INPUT_STOP_MOVE)
			{
				current_action = ENTITY_IDLE;
			}
			if (current_input == ENTITY_INPUT_DEATH)
			{
				current_action = ENTITY_DEATH;
			}
		}
		break;
		}

		previous_input = current_input;
		EntityEvent(ENTITY_STATE_CHANGE);
	}

	current_input = ENTITY_INPUT_NULL;
	return current_action;
}

void EntEnemyWolf::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyWolf::StateMachine()
{
	iPoint pos(position.x - 30, position.y + 30);
	switch (current_action)
	{
		//PIVOT DOESN'T CHANGE!
		//Related to the collider rect, not the sprite
	case ENTITY_IDLE:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 69;
		sprite_rect.h = sprite_dim.y = 54;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 94;
		sprite_rect.h = sprite_dim.y = 73;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 135;
		sprite_rect.h = sprite_dim.y = 103;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

		App->game->player->IncreaseBlood(blood_drop);
		App->game->player->PlayerEvent(BLOOD_UP);

		DropItem(pos);

		dead = true;
		break;


	case ENTITY_ATTACKING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 68;
		sprite_rect.h = sprite_dim.y = 54;
		sprite_pivot = sprite_dim / 2;
		//sprite_pivot.y += 5;

		break;
	}
}

void EntEnemyWolf::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 69;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 54;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
	sprite_pivot.y += 5;



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (54 + 1) * i, 69, 54, 12, 1);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (73 + 1) * i, 94, 73, 12, 1);
		tmp.speed = 0.4f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 135;
		int height = 103;
		int margin = 1;
		tmp.SetFrames(0, (height + margin) * i, width, height, 16, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		death.push_back(tmp);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 68;
		int height = 54;
		int margin = 1;
		tmp.SetFrames(0, (height + margin) * i, width, height, 10, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		attack.push_back(tmp);
	}
}