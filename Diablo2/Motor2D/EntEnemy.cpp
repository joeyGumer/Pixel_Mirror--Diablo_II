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
	//NOTE: have to change this, the random isn't equal at all. Even when there's a 60% to have no item, it almost always drops items
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (chance < 0)
		rarity = NO_DROP;
	else if (chance < 85)
		rarity = RARITY_COMMON;
	else if (chance < 95)
		rarity = RARITY_RARE;
	else if (chance >= 95)
		rarity = RARITY_LEGENDARY;


	if (rarity != NO_DROP)
	{
		chance = rand() % 100;

		if (chance < 65)
		{ 
			chance = rand() % 100;

			if (chance < 35)
			{
				itmStone* item;
				item = new itmStone(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 55)
			{
				itmRing* item;
				item = new itmRing(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 65)
			{
				itmJewel* item;
				item = new itmJewel(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 90)
			{
				itmRune* item;
				item = new itmRune(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance >= 90)
			{
				itmArmor* item;
				item = new itmArmor(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
		}
		else if (chance >= 65)
		{
			itmConsumable* item;
			item = new itmConsumable(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
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
		if (App->game->player->visible)
			return true;
		else
			return false;
	}

	return false;
}
//----------------------------


void EntEnemy::TakeDamage(float damage)
{
	//NOTE: this will be changed when the defense is applied
	HP_current -= damage;
	
	//Sounds-------
	if (enemy_type == ENEMY_CRAWLER)
		App->audio->PlayFx(App->game->em->crawler_gethitfx);
	if (enemy_type == ENEMY_WOLF)
		App->audio->PlayFx(App->game->em->wolf_gethitfx);
	if (enemy_type == ENEMY_SUMMONER)
		App->audio->PlayFx(App->game->em->summoner_gethitfx);
	if (enemy_type == ENEMY_COUNCIL)
		App->audio->PlayFx(App->game->em->council_gethitfx);
	if (enemy_type == ENEMY_SHAMAN)
		App->audio->PlayFx(App->game->em->shaman_gethitfx);
	if (enemy_type == ENEMY_IZUAL)
		App->audio->PlayFx(App->game->em->izual_gethitfx);
	if (enemy_type == ENEMY_ANDARIEL)
		App->audio->PlayFx(App->game->em->andariel_gethitfx);
	//-------------
	
	if (HP_current <= 0)
	{
		HP_current = 0;
		current_input = ENTITY_INPUT_DEATH;
		if (enemy_type == ENEMY_CRAWLER)
			App->audio->PlayFx(App->game->em->crawler_deathfx);
		if (enemy_type == ENEMY_WOLF)
			App->audio->PlayFx(App->game->em->wolf_deathfx);
		if (enemy_type == ENEMY_SUMMONER)
			App->audio->PlayFx(App->game->em->summoner_deathfx);
		if (enemy_type == ENEMY_COUNCIL)
			App->audio->PlayFx(App->game->em->council_deathfx);
		if (enemy_type == ENEMY_SHAMAN)
			App->audio->PlayFx(App->game->em->shaman_deathfx);
		if (enemy_type == ENEMY_NEST)
			App->audio->PlayFx(App->game->em->nest_deathfx);
		if (enemy_type == ENEMY_IZUAL)
			App->audio->PlayFx(App->game->em->izual_deathfx);
		if (enemy_type == ENEMY_ANDARIEL)
			App->audio->PlayFx(App->game->em->andariel_deathfx);
	}
}

void EntEnemy::DrawHPbar()
{
	//NOTE: make this to GUI so it can put the enemy's name
	//total_width = 220;
	int height = 20;
	int current_width = (total_width/HP_max)* HP_current;

	App->render->DrawQuad({ xpos/*220*/, 0, total_width, height }, 0, 0, 0, 150, true, false);
	App->render->DrawQuad({ xpos, 0, current_width, height }, 102, 0, 0, 150, true, false);
	
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
			if (enemy_type == ENEMY_CRAWLER)
				App->audio->PlayFx(App->game->em->crawler_attackfx);
			if (enemy_type == ENEMY_WOLF)
				App->audio->PlayFx(App->game->em->wolf_attackfx);
			if (enemy_type == ENEMY_SUMMONER)
				App->audio->PlayFx(App->game->em->summoner_attackfx);
			if (enemy_type == ENEMY_COUNCIL)
				App->audio->PlayFx(App->game->em->council_attackfx);
			if (enemy_type == ENEMY_SHAMAN)
				App->audio->PlayFx(App->game->em->shaman_attackfx);
			if (enemy_type == ENEMY_IZUAL)
				App->audio->PlayFx(App->game->em->izual_attackfx);
			if (enemy_type == ENEMY_ANDARIEL)
				App->audio->PlayFx(App->game->em->andariel_attackfx);
		}
	}
}