#include "EntEnemySummoner.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "Animation.h"
#include "j1SceneManager.h"
#include "j1Scene.h"


//Constructor
EntEnemySummoner::EntEnemySummoner(const iPoint &p, uint ID, int lvl) : EntEnemy(p, ID)
{
	name = "summoner";

	level = lvl;

	tex = idle_tex = App->game->em->summoner_idle;
	walk_tex = App->game->em->summoner_walk;
	death_tex = App->game->em->summoner_death;
	attack_tex = App->game->em->summoner_attack;

	SetAnimations();

	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_SUMMONER;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 10;
	HP_max = HP_current = 12;

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
	speed = 90.0f;

	//Attack
	random_range = 5;
	damage = 1;

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

	//Attack Range
	attack_range = 200.0f;

	//Spell Range
	summon_range = 100.0f;

	//Spell Cooldown
	summon_cooldown = 4;

	/*
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			summon_cooldown--;
		}
	}
	*/

	//Agro Range
	agro_range = 300.0f;

	//Pure Blood Drop
	blood_drop = 150;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			blood_drop += blood_drop / 2;
		}
	}

	//Particle Speed
	particle_speed = 250;

	//Timer Start
	summon_timer.Start();

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

EntEnemySummoner::~EntEnemySummoner()
{
	for (list<Entity*>::iterator item = summon_list.begin(); item != summon_list.end(); item++)
	{
		delete item._Ptr;
	}
}

//Update
bool EntEnemySummoner::Update(float dt)
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
				
				if (!tex_frozen)
				{
					/*
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
						*/

					tex_frozen = true;
				}
				//--------------

				dt = dt / 2;
			}
		}

		UpdateAction();

		fPoint player_pos = App->game->player->GetPivotPosition();

		if (ReadyToSummon() && App->game->player->visible)
		{
			attacking = true;
			current_input = ENTITY_INPUT_CAST;
			summon_timer.Start();
		}

		//NOTE: The enemy is for following the player one it has been founded, but for now, better not, because of the low framerate
		else if ((PlayerInRange()) && !attacking && last_update >= PATHFINDING_FRAMES)
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

		CheckToCast();
	

		switch (current_action)
		{
		case ENTITY_CASTING:
			UpdateSummon();
			break;
		case ENTITY_ATTACKING:
			UpdateRangedAttack();
		case ENTITY_WALKING:
			UpdateMovement(dt);
		}

		last_update++;
	}

	return true;
}

ENTITY_STATE EntEnemySummoner::UpdateAction()
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

void EntEnemySummoner::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemySummoner::StateMachine()
{
	iPoint pos(position.x - 30, position.y + 30);
	int r;

	switch (current_action)
	{
		//PIVOT DOESN'T CHANGE!
		//Related to the collider rect, not the sprite
	case ENTITY_IDLE:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 52;
		sprite_rect.h = sprite_dim.y = 94;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 20 };

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 98;
		sprite_rect.h = sprite_dim.y = 94;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 22 };

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 150;
		sprite_rect.h = sprite_dim.y = 149;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 40 };

		App->game->player->IncreaseBlood(blood_drop);
		App->game->player->PlayerEvent(BLOOD_UP);

		//Item out
		//r = rand() % 4;
		//if (r == 0)
		//NOTE: high risk of memory leaks!
		DropItem(pos);

		dead = true;
		break;


	case ENTITY_ATTACKING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 125;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 22 };

		break;

	case ENTITY_CASTING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 125;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 22 };

		break;
	}
}

void EntEnemySummoner::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 52;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 94;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (94 + 0) * i, 52, 94, 15, 0);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (94 + 0) * i, 98, 94, 18, 0);
		tmp.speed = 0.2f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 150;
		int height = 149;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 19, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		death.push_back(tmp);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 78;
		int height = 125;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 15, margin);
		tmp.loop = false;
		tmp.speed = 0.3f;

		attack.push_back(tmp);
	}
}

void EntEnemySummoner::SetParticles()
{
	particle_summoner.image = App->game->em->summoner_particle;

	particle_summoner.life = 5;
	particle_summoner.type = PARTICLE_ENEMY_CAST;
	particle_summoner.damage = damage;
	particle_summoner.speed.x = 0;
	particle_summoner.speed.y = 0;
	particle_summoner.anim.frames.push_back({ 0, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 64, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 128, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 192, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 256, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 320, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 384, 0, 64, 64 });
	particle_summoner.anim.frames.push_back({ 448, 0, 64, 64 });
	particle_summoner.anim.speed = 0.5f;
	particle_summoner.anim.loop = true;
	particle_summoner.anim.Reset();

	particle_summoner.collider_margin.x = particle_summoner.anim.GetCurrentFrame().w / 3;
	particle_summoner.collider_margin.y = particle_summoner.anim.GetCurrentFrame().h / 4;

	//Summon Particle
	particle_summon.image = App->game->em->summon_particle;
	particle_summon.life = 1;
	particle_summon.type = PARTICLE_BUFF;
	particle_summon.damage = 0;
	particle_summon.speed.x = 0;
	particle_summon.speed.y = 0;

	for (int i = 0; i < 3; i++)
	{
		particle_summon.anim.SetFrames(0, 0 + 136*i, 130, 136, 4);
	}

	particle_summon.anim.speed = 0.5f;
	particle_summon.anim.loop = false;
	particle_summon.anim.Reset();

}

void EntEnemySummoner::CheckToCast()
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
			current_input = ENTITY_INPUT_ATTACK;
			attacking = true;
			//NOTE: Insert attack sound here
		}
	}
}

void EntEnemySummoner::UpdateRangedAttack()
{
	if (current_animation->CurrentFrame() >= 7 && !particle_is_casted)
	{
		Particle* skill_particle = App->pm->AddParticle(particle_summoner, position.x, position.y - 40, 2, particle_summoner.image);
		particle_is_casted = true;
		skill_particle->SetPointSpeed(particle_speed, particle_destination);
	}

	if (current_animation->Finished())
	{
		particle_is_casted = false;
		attacking = false;
		current_animation->Reset();
		//input_locked = false;

		if (!enemy->Alive() || !PlayerInAttackRange() || ReadyToSummon())
		{
			current_input = ENTITY_INPUT_STOP_MOVE;
		}
	}
}

void EntEnemySummoner::UpdateSummon()
{
	iPoint pos = GetMapPosition();
	Particle* skill_particle = NULL;
	if (current_animation->CurrentFrame() >= 1 && !particle_is_casted)
	{
		particle_is_casted = true;

		int random = rand() % 4;
		if (random == 0)
		{
			pos.x += 3;
		}
		if (random == 1)
		{
			pos.y += 3;
		}
		if (random == 2)
		{
			pos.x -= 3;
		}
		if (random == 3)
		{
			pos.y -= 3;
		}

		iPoint _pos = App->map->MapToWorld(pos.x, pos.y);
		skill_particle = App->pm->AddParticle(particle_summon, _pos.x, _pos.y, 0.5f, particle_summon.image);
	}

	if (current_animation->CurrentFrame() >= 9 && !summoned)
	{
		Entity* to_summon = NULL;
		to_summon = App->game->em->AddEnemyMap(pos, ENEMY_WOLF, level);
		if (to_summon != NULL)
		{
			summon_list.push_back(to_summon);
			summoned = true;
		}
	}

	if (current_animation->Finished())
	{
		attacking = false;
		summoned = false;
		particle_is_casted = false;
		current_animation->Reset();

		current_input = ENTITY_INPUT_STOP_MOVE;
	}
}

bool EntEnemySummoner::PlayerInSummonRange()
{
	fPoint target_enemy = App->game->player->GetPivotPosition();

	fPoint dist;

	dist.x = target_enemy.x - position.x;
	dist.y = target_enemy.y - position.y;

	float ret = dist.GetModule();
	ret = ret;

	if (summon_range > ret)
	{
		return true;
	}

	return false;
}

bool EntEnemySummoner::ReadyToSummon()
{
	return PlayerInSummonRange() && !attacking && last_update >= PATHFINDING_FRAMES && summon_timer.ReadSec() >= summon_cooldown;
}