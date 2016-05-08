#include "EntEnemy.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "j1SceneManager.h"
#include "p2Point.h"
#include "snWin.h"
#include "snDungeon1.h"
#include "j1Collision.h"
#include "Item.h"
//Provisional?
#include "j1Audio.h"


//EntEnemy
//----------------------------

//Constructor
EntEnemy::EntEnemy(const iPoint &p, uint ID) : EntMobile(p, ID)
{
	blood_drop = 0;
	type = ENEMY;
}

void EntEnemy::DropItem(iPoint pos)
{
	//NOTE: thinking of using srand for more equally distributed random generation
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (chance < 60)
		rarity = NO_DROP;
	else if (chance >= 60 && chance < 85)
		rarity = RARITY_COMMON;
	else if (chance >= 85 && chance < 95)
		rarity = RARITY_RARE;
	else if (chance >= 95)
		rarity = RARITY_LEGENDARY;



	if (rarity != NO_DROP)
	{
		itmStone* test;
		test = new itmStone(rarity, pos);
		if (!test->ent_item)
		{
			RELEASE(test);
		}
	}

}

//Drawing methods
void EntEnemy::Draw()
{
	//iPoint pos = GetBlitPosition();

	if (sprite)
	{
		SDL_Rect current_sprite = current_animation->GetCurrentFrame();
		fPoint p = GetPivotPosition();
		iPoint pos(p.x, p.y);
		sprite->UpdateSprite(tex, pos, sprite_pivot, current_sprite);
	}

}

void EntEnemy::DrawDebug()
{
	iPoint t_pos = GetTilePosition();
	fPoint p_pos = GetPivotPosition();
	SDL_Rect rect = GetPlayerRect();

	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0, 255, false);

	App->render->DrawQuad(rect, 255, 0, 0, 255, false);

	App->render->DrawCircle(p_pos.x, p_pos.y, attack_range, 255, 0, 0);
	App->render->DrawCircle(p_pos.x, p_pos.y, agro_range, 0, 0, 255);
}


bool EntEnemy::PlayerInRange()
{
	fPoint target_enemy = App->game->player->GetPivotPosition();

	fPoint dist;

	dist.x = target_enemy.x - position.x;
	dist.y = target_enemy.y - position.y;

	float ret = dist.GetModule();
	ret = ret;

	if (agro_range > ret)
	{
		return true;
	}

	return false;
}
//----------------------------


void EntEnemy::TakeDamage(int damage)
{
	//NOTE: this will be changed when the defense is applied
	HP_current -= damage;
	
	//Sounds-------
	if (name == "crawler")
		App->audio->PlayFx(App->game->em->crawler_gethitfx);
	if (name == "wolf")
		App->audio->PlayFx(App->game->em->wolf_gethitfx);
	//-------------
	
	if (HP_current <= 0)
	{
		HP_current = 0;
		current_input = ENTITY_INPUT_DEATH;
		if (name == "crawler")
			App->audio->PlayFx(App->game->em->crawler_deathfx);
		if (name == "wolf")
			App->audio->PlayFx(App->game->em->wolf_deathfx);
	}
}

void EntEnemy::DrawHPbar()
{
	//NOTE: make this to GUI so it can put the enemy's name
	float total_width = 200;
	int height = 20;
	int current_width = (total_width/HP_max)* HP_current;

	App->render->DrawQuad({ 220, 0, total_width, height }, 0, 0, 0, 255, true, false);
	App->render->DrawQuad({ 220, 0, current_width, height }, 255, 0, 0, 255, true, false);

}

/*
//---- Attack
*/

bool EntEnemy::PlayerInAttackRange()
{
	fPoint target_enemy = App->game->player->GetPivotPosition();

	fPoint dist;

	dist.x = target_enemy.x - position.x;
	dist.y = target_enemy.y - position.y;

	float ret = dist.GetModule();

	if (attack_range > ret)
	{
		return true;
	}

	return false;
}

void EntEnemy::UpdateAttack()
{
	if (current_animation->Finished())
	{
		if (!enemy->Alive() || !PlayerInAttackRange())
		{
			current_input = ENTITY_INPUT_STOP_MOVE;
		}
			
		attacking = false;
		current_animation->Reset();
		//input_locked = false;
	}
}
void EntEnemy::CheckToAttack()
{
	if (enemy && !attacking)
	{
		if (PlayerInAttackRange())
		{

			fPoint target = enemy->GetPivotPosition();

			fPoint dist = { target - position };
			velocity = dist;

			SetDirection();

			enemy->TakeDamage(damage);

			movement = false;
			current_input = ENTITY_INPUT_ATTACK;
			attacking = true;
			if (name == "crawler")
				App->audio->PlayFx(App->game->em->crawler_attackfx);
			if (name == "wolf")
				App->audio->PlayFx(App->game->em->wolf_attackfx);
		}
	}
}
//EntEnemyWolf
//----------------------------

//Constructor
EntEnemyWolf::EntEnemyWolf(const iPoint &p, uint ID) : EntEnemy(p, ID)
{
	name = "wolf";
	tex = idle_tex = App->tex->Load("textures/wolf.png");
	walk_tex = App->tex->Load("textures/wolf_walk.png");
	death_tex = App->tex->Load("textures/wolf_death.png");
	attack_tex = App->tex->Load("textures/wolf_attack.png");

	SetAnimations();
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	HP_max = HP_current = 100;
	speed = 100.0f;

	movement = false;
	enemy_type = ENEMY_WOLF;

	attack_range = 50.0f;
	agro_range = 150.0f;

	damage = 3;

	last_update = PATHFINDING_FRAMES;

	collider = App->collision->AddCollider(GetPlayerRect(), COLLIDER_ENEMY, App->game->em);

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
		tmp.speed = 0.2f;

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

//-----------------------------

//EntEnemyCrawler
//----------------------------

//Constructor
EntEnemyCrawler::EntEnemyCrawler(const iPoint &p, uint ID) : EntEnemy(p, ID)
{
	name = "crawler";
	tex = idle_tex = App->game->em->crawler_idle;
	walk_tex = App->game->em->crawler_walk;
	death_tex = App->game->em->crawler_death;
	attack_tex = App->game->em->crawler_attack;

	SetAnimations();
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_CRAWLER;

	HP_max = HP_current = 100;
	speed = 100.0f;

	movement = false;

	attack_range = 50.0f;
	agro_range = 190.0f;

	damage = 5;

	blood_drop = 50;

	last_update = PATHFINDING_FRAMES;

	collider = App->collision->AddCollider(GetPlayerRect(), COLLIDER_ENEMY, App->game->em);

	//Sprite creation

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();
	sprite = new Sprite(tex, pos, sprite_pivot, current_sprite);
	App->render->AddSpriteToList(sprite);

}

//Update
bool EntEnemyCrawler::Update(float dt)
{
	if (!dead)
	{
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

ENTITY_STATE EntEnemyCrawler::UpdateAction()
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
			if (current_input == INPUT_DEATH)
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

void EntEnemyCrawler::EntityEvent(ENTITY_EVENT even)
{
	switch (even)
	{
	case ENTITY_STATE_CHANGE:
	{
		StateMachine();
	}
	}
}

void EntEnemyCrawler::StateMachine()
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

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 51;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 54;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 90;
		sprite_rect.h = sprite_dim.y = 56;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 5;

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

		sprite_rect.w = sprite_dim.x = 170;
		sprite_rect.h = sprite_dim.y = 81;
		sprite_pivot = sprite_dim / 2;
		sprite_pivot.y += 17;

		break;
	}
}

void EntEnemyCrawler::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 78;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 51;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
	sprite_pivot.y += 5;



	//NOTE: Do it like a player, no number, variables
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (51 + 0) * i, 78, 51, 4, 0);
		tmp.speed = 0.2f;

		idle.push_back(tmp);
	}


	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, (54 + 0) * i, 78, 54, 9, 0);
		tmp.speed = 0.2f;

		walk.push_back(tmp);
	}

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 90;
		int height = 56;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 12, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		death.push_back(tmp);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		int width = 170;
		int height = 81;
		int margin = 0;
		tmp.SetFrames(0, (height + margin) * i, width, height, 10, margin);
		tmp.loop = false;
		tmp.speed = 0.2f;

		attack.push_back(tmp);
	}
}

//-----------------------------

//EntEnemyBoss
//----------------------------

//Constructor
EntEnemyCouncil::EntEnemyCouncil(const iPoint &p, uint ID) : EntEnemy(p, ID)
{
	name = "council member";
	tex = idle_tex = App->game->em->boss_idle;
	walk_tex = App->game->em->boss_walk;
	death_tex = App->game->em->boss_death;
	attack_tex = App->game->em->boss_attack;

	SetAnimations();
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	enemy_type = ENEMY_COUNCIL;

	HP_max = HP_current = 400;
	speed = 100.0f;

	movement = false;

	attack_range = 50.0f;
	agro_range = 150.0f;

	damage = 7;

	last_update = PATHFINDING_FRAMES;

	collider = App->collision->AddCollider(GetPlayerRect(), COLLIDER_ENEMY, App->game->em);

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
	else
	{
		if (win.ReadSec() > 5)
		{
			App->sm->dungeon1->win = true;
		}
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
		sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
		sprite_pivot.y += 5;

		break;

	case ENTITY_WALKING:
		tex = walk_tex;
		current_animation_set = walk;

		sprite_rect.w = sprite_dim.x = 78;
		sprite_rect.h = sprite_dim.y = 54;
		sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
		sprite_pivot.y += 7;
		sprite_pivot.x += 45;

		break;

	case ENTITY_DEATH:
		tex = death_tex;
		current_animation_set = death;

		sprite_rect.w = sprite_dim.x = 190;
		sprite_rect.h = sprite_dim.y = 129;
		sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
		sprite_pivot.y += 5;
		sprite_pivot.x += 40;

		win.Start();

		dead = true;

		break;


	case ENTITY_ATTACKING:
		tex = attack_tex;
		current_animation_set = attack;

		sprite_rect.w = sprite_dim.x = 170;
		sprite_rect.h = sprite_dim.y = 81;
		sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
		sprite_pivot.y += 5;
		sprite_pivot.x += 30;

		break;
	}
}

void EntEnemyCouncil::SetAnimations()
{
	//NOTE: this should not go here
	collider_rect.w = sprite_rect.w = sprite_dim.x = 77;
	collider_rect.h = sprite_rect.h = sprite_dim.y = 97;

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20 };
	sprite_pivot.y += 5;



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
}