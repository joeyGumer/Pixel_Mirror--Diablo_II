#include "EntEnemyAndariel.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "Animation.h"
#include "snDungeon2.h"
#include "snDungeon3.h"
#include "snOutdoor2.h"
#include "j1SceneManager.h"


//Constructor
EntEnemyAndariel::EntEnemyAndariel(const iPoint &p, uint ID, int lvl) : EntEnemy(p, ID)
{
	name = "andariel";

	level = lvl;

	tex = idle_tex = App->game->em->andariel_idle;
	walk_tex = App->game->em->andariel_walk;
	death_tex = App->game->em->andariel_death;
	attack_tex = App->game->em->andariel_attack;
	cast_tex = App->game->em->andariel_cast;

	SetAnimations();


	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_ANDARIEL;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 51;
	HP_max = HP_current = 150;

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
	speed = 100.0f;

	//Melee Attack
	random_range = 11;
	damage = 10;

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
	attack_range = 70.0f;

	//Spell Attack
	random_range = 16;
	magic_damage = 5;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			magic_damage *= 2;
			random_range *= 2;
		}
	}
	random = rand() % random_range;
	magic_damage += random;

	//Spell Range
	magic_range = 275.0f;

	//Spell Cooldown
	magic_cooldown = 5;
	/*
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			magic_cooldown--;
		}
	}
	*/

	//Agro Range
	agro_range = 320.0f;

	//Pure Blood Drop
	blood_drop = 1500;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			blood_drop += blood_drop / 2;
		}
	}

	//Rows
	row_number = 2;
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			row_number++;
		}
	}

	magic_timer.Start();
	//------------------------------------

	SetParticles();
	last_update = PATHFINDING_FRAMES;

	SDL_Rect col_rect;

	col_margin.x = 5;
	col_margin.y = 5;

	col_pivot.x = 0;
	col_pivot.y = 0;

	col_rect.x = GetPlayerRect().x + col_margin.x + col_pivot.x;
	col_rect.y = GetPlayerRect().y + col_margin.y + col_pivot.y;
	col_rect.w = GetPlayerRect().w - col_margin.x * 2;
	col_rect.h = GetPlayerRect().h - col_margin.y * 2;

	collider = App->collision->AddCollider(col_rect, COLLIDER_ENEMY, App->game->em);

	//Sprite creation

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();
	sprite = new Sprite(tex, pos, sprite_pivot, current_sprite);
	App->render->AddSpriteToList(sprite);

}

//Update
bool EntEnemyAndariel::Update(float dt)
{
	if (!dead)
	{
		if (frozen)
		{
			if (freeze_timer.ReadSec() >= freeze_time)
			{
				frozen = false;
			}
			else
			{
				dt = dt / 2;
			}
		}

		UpdateAction();

		fPoint player_pos = App->game->player->GetPivotPosition();

		if (ReadyToCast() && App->game->player->visible && enemy != NULL)
		{
			attacking = true;
			current_input = ENTITY_INPUT_CAST;

			particle_destination.x = enemy->p_position.x;
			particle_destination.y = enemy->p_position.y - 40;

			SetDirection(particle_destination);

			magic_timer.Start();
		}

		//NOTE: The enemy is for following the player one it has been founded, but for now, better not, because of the low framerate
		else if ((PlayerInRange() /*|| enemy*/) && !attacking && last_update >= PATHFINDING_FRAMES)
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
		case ENTITY_CASTING:
			UpdateRangedAttack();
			break;
		case ENTITY_ATTACKING:
			UpdateAttack();
		case ENTITY_WALKING:
			UpdateMovement(dt);
		}

		last_update++;
	}

	else
	{
		if (win.ReadSec() > 0 && !portal_appeared)
		{
			if (App->sm->GetCurrentScene() == App->sm->dungeon2)
			{
				iPoint pos;
				pos.x = position.x;
				pos.y = position.y+10;
				App->sm->dungeon2->AddPortal(pos);
			}
			if (App->sm->GetCurrentScene() == App->sm->outdoor2)
			{
				iPoint pos;
				pos.x = position.x;
				pos.y = position.y+10;
				App->sm->outdoor2->AddPortal(pos);
			}
			if (App->sm->GetCurrentScene() == App->sm->dungeon3)
			{
				iPoint pos;
				pos.x = position.x;
				pos.y = position.y + 10;
				App->sm->dungeon3->AddPortal(pos);
			}
			portal_appeared = true;
		}
	}

	return true;
}

ENTITY_STATE EntEnemyAndariel::UpdateAction()
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
			if (current_input == ENTITY_INPUT_CAST)
			{
				current_action = ENTITY_CASTING;
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
			if (current_input == ENTITY_INPUT_CAST)
			{
				current_action = ENTITY_CASTING;
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

		case ENTITY_CASTING:
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

void EntEnemyAndariel::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyAndariel::StateMachine()
{
	iPoint pos(position.x - 30, position.y + 30);
	switch (current_action)
	{
		//PIVOT DOESN'T CHANGE!
		//Related to the collider rect, not the sprite
	case ENTITY_IDLE:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 178;
		sprite_rect.h = sprite_dim.y = 179;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 20 };

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 148;
		sprite_rect.h = sprite_dim.y = 184;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 22 };

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 253;
		sprite_rect.h = sprite_dim.y = 232;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 40 };

		App->game->player->IncreaseBlood(blood_drop);
		App->game->player->PlayerEvent(BLOOD_UP);

		//Item out
		//r = rand() % 4;
		//if (r == 0)
		//NOTE: high risk of memory leaks!
		DropItem(pos);

		win.Start();

		dead = true;
		break;


	case ENTITY_ATTACKING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 247;
		sprite_rect.h = sprite_dim.y = 248;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 40 };

		break;

	case ENTITY_CASTING:
		tex = cast_tex;
		current_animation_set = cast;

		sprite_rect.w = sprite_dim.x = 212;
		sprite_rect.h = sprite_dim.y = 182;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 24 };

		break;
	}
}

void EntEnemyAndariel::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 178;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 179;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 178;
		int height = 179;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 16, margin);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 148;
		int height = 184;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 12, margin);
		tmp.speed = 0.2f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 203;
		int height = 232;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 23, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		death.push_back(tmp);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 247;
		int height = 248;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 16, margin);
		tmp.loop = false;
		tmp.speed = 0.3f;

		attack.push_back(tmp);
	}

	//Cast
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 212;
		int height = 182;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 18, margin);
		tmp.loop = false;
		tmp.speed = 0.3f;

		cast.push_back(tmp);
	}
}

void EntEnemyAndariel::SetParticles()
{
	particle.image = App->game->em->andariel_particle;

	particle.life = 5;
	particle.type = PARTICLE_ENEMY_CAST;
	particle.damage = magic_damage;
	particle.speed.x = 0;
	particle.speed.y = 0;
	
	for (int i = 0; i < 5; i++)
	{
		particle.anim.SetFrames(0, 0 + 100 * i, 32, 100, 5);
	}

	particle.anim.speed = 0.5f;
	particle.anim.loop = true;
	particle.anim.Reset();

	particle.collider_margin.x = particle.anim.GetCurrentFrame().w / 5;
	particle.collider_margin.y = particle.anim.GetCurrentFrame().h / 3 + 10;

	particle.collider_pivot.y = 40;

}

void EntEnemyAndariel::CheckToCast()
{
	if (enemy && !attacking)
	{
		if (PlayerInAttackRange())
		{
			fPoint target = enemy->GetPivotPosition();

			fPoint dist = { target - position };
			velocity = dist;

			SetDirection();

			particle_destination.x = enemy->p_position.x;
			particle_destination.y = enemy->p_position.y - 40;

			movement = false;
			current_input = ENTITY_INPUT_CAST;
			attacking = true;
			//NOTE: Insert attack sound here
		}
	}
}

void EntEnemyAndariel::UpdateRangedAttack()
{
	SetDirection(particle_destination);
	if (current_animation->CurrentFrame() >= 7 && !particle_is_casted)
	{
		particle_is_casted = true;

		int marginX = -100;
		int marginY = -100;

		for (int i = 0; i < row_number; i++)
		{
			int random_rangeX = rand() % 201;
			int random_rangeY = rand() % 201;

			int random2 = rand() % 2;
			if (random2 == 0)
			{
				random2 = -1;
			}

			for (int j = 0; j < 5; j++)
			{
				Particle* skill_particle1 = App->pm->AddParticle(particle, particle_destination.x + marginX + random_rangeX, particle_destination.y + marginY + random_rangeY + 25 * j * random2, 3, particle.image);
			}
			
		}
	}

	if (current_animation->Finished())
	{
		particle_is_casted = false;
		attacking = false;
		current_animation->Reset();
		//input_locked = false;

		if (!enemy->Alive() || !ReadyToCast())
		{
			current_input = ENTITY_INPUT_STOP_MOVE;
		}
	}
}

bool EntEnemyAndariel::PlayerInCastRange()
{
	fPoint target_enemy = App->game->player->GetPivotPosition();

	fPoint dist;

	dist.x = target_enemy.x - position.x;
	dist.y = target_enemy.y - position.y;

	float ret = dist.GetModule();
	ret = ret;

	if (magic_range > ret)
	{
		return true;
	}

	return false;
}

bool EntEnemyAndariel::ReadyToCast()
{
	return PlayerInCastRange() && !attacking && last_update >= PATHFINDING_FRAMES && magic_timer.ReadSec() >= magic_cooldown;
}