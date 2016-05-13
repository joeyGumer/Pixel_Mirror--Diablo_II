#include "EntEnemyIzual.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "Animation.h"
#include "snDungeon2.h"
#include "snOutdoor2.h"
#include "j1SceneManager.h"
#include "EntPortal.h"


//Constructor
EntEnemyIzual::EntEnemyIzual(const iPoint &p, uint ID, int lvl) : EntEnemy(p, ID)
{
	name = "izual";

	level = lvl;

	tex = idle_tex = App->game->em->izual_idle;
	walk_tex = App->game->em->izual_walk;
	death_tex = App->game->em->izual_death;
	attack_tex = App->game->em->izual_attack;
	cast_tex = App->game->em->izual_cast;

	SetAnimations();
	

	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_IZUAL;

	//Attirbutes
	//------------------------------------
	//Life
	int random_range = 51;
	HP_max = HP_current = 175;

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
	random_range = 21;
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
	attack_range = 80.0f;

	//Spell Attack
	random_range = 11;
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
	magic_cooldown = 4;
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

	//Magic Counter
	magic_counter = 5;
	for (int i = 0; i < level; i++)
	{
		if (i > 0)
		{
			magic_counter += 2;
		}
	}

	magic_timer.Start();
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

//Update
bool EntEnemyIzual::Update(float dt)
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

		if (ReadyToCast() && App->game->player->visible)
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
			portal_appeared = true;
		}
	}

	return true;
}

ENTITY_STATE EntEnemyIzual::UpdateAction()
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

void EntEnemyIzual::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyIzual::StateMachine()
{
	iPoint pos(position.x - 30, position.y + 30);
	switch (current_action)
	{
		//PIVOT DOESN'T CHANGE!
		//Related to the collider rect, not the sprite
	case ENTITY_IDLE:
		tex = idle_tex;
		current_animation_set = idle;

		sprite_rect.w = sprite_dim.x = 158;
		sprite_rect.h = sprite_dim.y = 119;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 20 };

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 153;
		sprite_rect.h = sprite_dim.y = 119;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 22 };

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 253;
		sprite_rect.h = sprite_dim.y = 189;
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

		sprite_rect.w = sprite_dim.x = 179;
		sprite_rect.h = sprite_dim.y = 176;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 40 };

		break;

	case ENTITY_CASTING:
		tex = cast_tex;
		current_animation_set = cast;

		sprite_rect.w = sprite_dim.x = 190;
		sprite_rect.h = sprite_dim.y = 175;
		sprite_pivot = { sprite_rect.w / 2, sprite_rect.h - 24 };

		break;
	}
}

void EntEnemyIzual::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 158;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 119;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (119 + 0) * i, 158, 119, 8, 0);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (119 + 0) * i, 153, 119, 8, 0);
		tmp.speed = 0.2f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 253;
		int height = 189;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 20, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		death.push_back(tmp);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 179;
		int height = 176;
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
		int width = 190;
		int height = 175;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 16, margin);
		tmp.loop = false;
		tmp.speed = 0.3f;

		cast.push_back(tmp);
	}
}

void EntEnemyIzual::SetParticles()
{
	particle_izual.image = App->game->em->izual_particle;

	particle_izual.life = 5;
	particle_izual.type = PARTICLE_ENEMY_CAST;
	particle_izual.damage = 20;
	particle_izual.speed.x = 0;
	particle_izual.speed.y = 0;
	particle_izual.anim.frames.push_back({ 0, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 64, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 128, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 192, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 256, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 320, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 384, 0, 64, 64 });
	particle_izual.anim.frames.push_back({ 448, 0, 64, 64 });
	particle_izual.anim.speed = 0.5f;
	particle_izual.anim.loop = true;
	particle_izual.anim.Reset();

	particle_izual.collider_margin.x = particle_izual.anim.GetCurrentFrame().w / 3;
	particle_izual.collider_margin.y = particle_izual.anim.GetCurrentFrame().h / 4;

}

void EntEnemyIzual::CheckToCast()
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

void EntEnemyIzual::UpdateRangedAttack()
{
	SetDirection(particle_destination);
	if (current_animation->CurrentFrame() >= 7 && !particle_is_casted)
	{
		particle_is_casted = true;

		int marginX = -85;
		int marginY = -85;

		for (int i = 0; i < magic_counter; i++)
		{
			int random_rangeX = rand() % 171;
			int random_rangeY = rand() % 171;

			int random1 = rand() % 2;
			if (random1 == 0)
			{
				random1 = -1;
			}

			int random2 = rand() % 2;
			if (random2 == 0)
			{
				random2 = -1;
			}
			Particle* skill_particle1 = App->pm->AddParticle(particle_izual, position.x, position.y - 40, 3, particle_izual.image);
			skill_particle1->SetPointSpeed(150, { particle_destination.x + marginX + random_rangeX * random1, particle_destination.y + marginY + random_rangeY * random2 });
		}

		/*
		
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

		*/
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

bool EntEnemyIzual::PlayerInCastRange()
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

bool EntEnemyIzual::ReadyToCast()
{
	return PlayerInCastRange() && !attacking && last_update >= PATHFINDING_FRAMES && magic_timer.ReadSec() >= magic_cooldown;
}