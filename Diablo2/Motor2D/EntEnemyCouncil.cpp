#include "EntEnemyCouncil.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "snDungeon1.h"
#include "snDungeon2.h"
#include "j1SceneManager.h"

//Constructor
EntEnemyCouncil::EntEnemyCouncil(const iPoint &p, uint ID) : EntEnemy(p, ID)
{
	name = "council member";
	tex = idle_tex = App->game->em->boss_idle;
	walk_tex = App->game->em->boss_walk;
	death_tex = App->game->em->boss_death;
	attack_tex = App->game->em->boss_attack;
	cast_tex = App->game->em->boss_cast;

	SetAnimations();
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_COUNCIL;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 16;
	HP_max = HP_current = 25;

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
	speed = 120.0f;

	//Melee Attack
	random_range = 5;
	damage = 7;

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
	attack_range = 65.0f;

	//Spell Attack
	random_range = 5;
	magic_damage = 10;

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
	magic_range = 150.0f;

	//Spell Cooldown
	magic_cooldown = 4;
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			magic_cooldown--;
		}
	}

	//Agro Range
	agro_range = 200.0f;

	//Pure Blood Drop
	blood_drop = 250;

	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			blood_drop += blood_drop / 2;
		}
	}

	magic_timer.Start();
	//------------------------------------

	SetParticles();
	last_update = PATHFINDING_FRAMES;

	SDL_Rect col_rect;

	iPoint col_margin;
	col_margin.x = 15;
	col_margin.y = 15;

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

//Update
bool EntEnemyCouncil::Update(float dt)
{
	if (!dead)
	{
		UpdateAction();

		fPoint player_pos = App->game->player->GetPivotPosition();

		if (ReadyToCast())
		{
			attacking = true;
			current_input = ENTITY_INPUT_CAST;

			particle_destination.x = enemy->p_position.x;
			particle_destination.y = enemy->p_position.y - 40;

			SetDirection(particle_destination);

			magic_timer.Start();
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

		CheckToAttack();

		switch (current_action)
		{
		case ENTITY_CASTING:
			UpdateCast();
			break;
		case ENTITY_ATTACKING:
			UpdateAttack();
		case ENTITY_WALKING:
			UpdateMovement(dt);
		}

		last_update++;
	}

	return true;
}

ENTITY_STATE EntEnemyCouncil::UpdateAction()
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

void EntEnemyCouncil::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyCouncil::StateMachine()
{
	//NOTE: so maaaany wrong things
	iPoint pos(position.x - 30, position.y + 30);
	switch (current_action)
	{
		//NOTE: so maaaany wrong things
		//PIVOT DOESN'T CHANGE!
		//Related to the collider rect, not the sprite
	case ENTITY_IDLE:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 51;
		sprite_pivot = { collider_rect.w / 2, collider_rect.h - 20 };

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 54;
		sprite_pivot = { (collider_rect.w / 2) + 30, collider_rect.h - 10 };

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 190;
		sprite_rect.h = sprite_dim.y = 129;
		sprite_pivot = { (collider_rect.w / 2) + 30, collider_rect.h - 10 };

		App->game->player->IncreaseBlood(blood_drop);
		App->game->player->PlayerEvent(BLOOD_UP);

		DropItem(pos);

		dead = true;

		break;


	case ENTITY_ATTACKING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 170;
		sprite_rect.h = sprite_dim.y = 81;
		sprite_pivot = { (collider_rect.w / 2) + 30, collider_rect.h - 10 };

		break;

	case ENTITY_CASTING:
		tex = cast_tex;
		current_animation_set = cast;

		sprite_rect.w = sprite_dim.x = 106;
		sprite_rect.h = sprite_dim.y = 129;
		sprite_pivot = { (collider_rect.w / 2) + 10, collider_rect.h - 0 };

		break;
	}
}

void EntEnemyCouncil::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 77;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 97;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (97 + 0) * i, 77, 97, 7, 0);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (117 + 0) * i, 140, 117, 11, 0);
		tmp.speed = 0.2f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 190;
		int height = 129;
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
		int width = 150;
		int height = 105;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 10, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		attack.push_back(tmp);
	}

	//Cast
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 106;
		int height = 129;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 14, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		cast.push_back(tmp);
	}
}

void EntEnemyCouncil::SetParticles()
{
	particle.image = App->game->em->boss_particle;

	particle.life = 5;
	particle.type = PARTICLE_ENEMY_CAST;
	particle.damage = magic_damage;
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

void EntEnemyCouncil::UpdateCast()
{
	SetDirection(particle_destination);
	if (current_animation->CurrentFrame() >= 7 && !particle_is_casted)
	{
		particle_is_casted = true;
		Particle* skill_particle1 = App->pm->AddParticle(particle, particle_destination.x + 50, particle_destination.y + 50, 5, particle.image);
		Particle* skill_particle2 = App->pm->AddParticle(particle, particle_destination.x - 50, particle_destination.y - 50, 5, particle.image);
		Particle* skill_particle3 = App->pm->AddParticle(particle, particle_destination.x + 50, particle_destination.y - 50, 5, particle.image);
		Particle* skill_particle4 = App->pm->AddParticle(particle, particle_destination.x - 50, particle_destination.y + 50, 5, particle.image);
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

bool EntEnemyCouncil::ReadyToCast()
{
	return PlayerInCastRange() && !attacking && last_update >= PATHFINDING_FRAMES && magic_timer.ReadSec() >= magic_cooldown;
}

bool EntEnemyCouncil::PlayerInCastRange()
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