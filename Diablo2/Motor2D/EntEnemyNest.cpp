#include "EntEnemyNest.h"
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
#include "snDungeon2.h"
#include "snDungeon3.h"
#include "snOutdoor2.h"


//Constructor
EntEnemyNest::EntEnemyNest(const iPoint &p, uint ID, int lvl) : EntEnemy(p, ID)
{
	name = "nest";

	level = lvl;

	tex = idle_tex = App->game->em->nest_idle;
	death_tex = App->game->em->nest_death;
	attack_tex = App->game->em->nest_cast;

	SetAnimations();

	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_NEST;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 51;
	HP_max = HP_current = 200;

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
	random_range = 16;
	damage = 15;

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

	//Attack Cooldown
	ranged_cooldown = 2;

	//Spell Range
	summon_range = 300.0f;

	//Spell Cooldown
	summon_cooldown = 5;
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
	blood_drop = 1500;

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
	ranged_timer.Start();

	//Columns
	ranged_columns = 4;
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			ranged_columns++;
		}
	}
	//------------------------------------

	SetParticles();
	last_update = PATHFINDING_FRAMES;

	SDL_Rect col_rect;

	iPoint col_margin;
	col_margin.x = 5;
	col_margin.y = 5;

	iPoint col_pivot;
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

EntEnemyNest::~EntEnemyNest()
{
	for (list<Entity*>::iterator item = summon_list.begin(); item != summon_list.end(); item++)
	{
		delete item._Ptr;
	}
}

//Update
bool EntEnemyNest::Update(float dt)
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
		else if ((PlayerInRange()) && !attacking && last_update >= PATHFINDING_FRAMES
			&& ranged_timer.ReadSec() >= ranged_cooldown)
		{
			last_update = 0;
			int target_x = player_pos.x;
			int target_y = player_pos.y;

			iPoint _target = { target_x, target_y };
			_target = App->map->WorldToMap(_target.x, _target.y);

			enemy = App->game->player;
			ranged_timer.Start();
		}

		CheckToCast();


		switch (current_action)
		{
		case ENTITY_CASTING:
			UpdateSummon();
			break;
		case ENTITY_ATTACKING:
			UpdateRangedAttack();
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

ENTITY_STATE EntEnemyNest::UpdateAction()
{
	if (current_input != ENTITY_INPUT_NULL && current_input != previous_input)
	{
		switch (current_action)
		{
		case ENTITY_IDLE:
		{
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

void EntEnemyNest::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyNest::StateMachine()
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

		sprite_rect.w = sprite_dim.x = 122;
		sprite_rect.h = sprite_dim.y = 174;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 20 };

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 206;
		sprite_rect.h = sprite_dim.y = 243;
		sprite_pivot = { (sprite_rect.w / 2) - 20, sprite_rect.h - 40 };

		App->game->player->IncreaseBlood(blood_drop);
		App->game->player->PlayerEvent(BLOOD_UP);

		DropItem(pos);

		dead = true;
		break;


	case ENTITY_ATTACKING:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 122;
		sprite_rect.h = sprite_dim.y = 174;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 20 };

		break;

	case ENTITY_CASTING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 124;
		sprite_rect.h = sprite_dim.y = 189;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 25 };

		break;
	}
}

void EntEnemyNest::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 122;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 174;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, 0, 122, 174, 21, 1);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp2;
		int width = 206;
		int height = 243;
		int margin = 1;
		tmp2.SetFrames(0, 0, width, height, 21, margin);
		tmp2.loop = false;
		tmp2.speed = 0.2f;

		death.push_back(tmp2);
	}


	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp3;
		int width = 124;
		int height = 189;
		int margin = 1;
		tmp3.SetFrames(0, 0, width, height, 31, margin);
		tmp3.loop = false;
		tmp3.speed = 0.3f;

		attack.push_back(tmp3);
	}
}

void EntEnemyNest::SetParticles()
{
	particle.image = App->game->em->nest_particle;

	particle.life = 5;
	particle.type = PARTICLE_ENEMY_CAST;
	particle.damage = damage;
	particle.speed.x = 0;
	particle.speed.y = 0;
	particle.anim.SetFrames(0, 0, 87, 112, 20);
	particle.anim.speed = 0.5f;
	particle.anim.loop = true;
	particle.anim.Reset();

	particle.collider_margin.x = particle.anim.GetCurrentFrame().w / 3;
	particle.collider_margin.y = particle.anim.GetCurrentFrame().h / 4;
	particle.collider_pivot.y = 15;

}

void EntEnemyNest::CheckToCast()
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

void EntEnemyNest::UpdateRangedAttack()
{
	if (current_animation->CurrentFrame() >= 7 && !particle_is_casted)
	{
		particle_is_casted = true;

		int marginX = -150;
		int marginY = -150;

		for (int i = 0; i < ranged_columns; i++)
		{
			int random_rangeX = rand() % 301;
			int random_rangeY = rand() % 301;
			Particle* skill_particle1 = App->pm->AddParticle(particle, particle_destination.x + marginX + random_rangeX, particle_destination.y + marginY + random_rangeY, 3, particle.image);
		}
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

void EntEnemyNest::UpdateSummon()
{
	if (current_animation->CurrentFrame() >= 29 && !summoned)
	{
		Entity* to_summon = NULL;
		iPoint pos = GetMapPosition();
		pos.x -= 2;
		pos.y += 2;
		to_summon = App->game->em->AddEnemyMap(pos, ENEMY_CRAWLER, level);
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
		current_animation->Reset();

		current_input = ENTITY_INPUT_STOP_MOVE;
	}
}

bool EntEnemyNest::PlayerInSummonRange()
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

bool EntEnemyNest::ReadyToSummon()
{
	return PlayerInSummonRange() && !attacking && last_update >= PATHFINDING_FRAMES && summon_timer.ReadSec() >= summon_cooldown;
}