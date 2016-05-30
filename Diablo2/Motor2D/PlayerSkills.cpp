#include "PlayerSkills.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1Render.h"
#include "j1EntityManager.h"
#include "entEnemy.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Map.h"
//#include "playerParticle.h" 
#include "j1ParticleManager.h"
#include "j1Collision.h"

/*
//--Basic Attack
*/

//NOTE: provisional
sklBasicAttack::sklBasicAttack() : sklMelee()
{
	//NOTE : Has to be unloaded somewhere
	skill_tex = App->tex->Load("textures/vamp_attack.png");
}

sklBasicAttack::~sklBasicAttack()
{
	App->tex->UnLoad(skill_tex);
}

void sklBasicAttack::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() == 12 && player->attacking == true)
	{
		SkillEffect();
	}
	else if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}

void sklBasicAttack::SkillEffect()
{
	//Damage calculation
	float final_damage = player->atk_damage_final_down;
	final_damage += rand() % (player->atk_damage_final_up + 1 - player->atk_damage_final_down);

	//if extra damage
	final_damage += ((float(final_damage) / 100) * float(player->extra_damage));

	player->enemy->TakeDamage(final_damage);

	player->RestoreHP(player->life_steal);

	//Lust influence
	if (player->lust->unlocked)
	{
		player->ChangeMP(player->lust->basic_blood_charges);
	}

	//App->audio->PlayFx(player_attack, 0);
	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;


}

void sklBasicAttack::SetSkillAnimations()
{
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 20, SPRITE_MARGIN);
		atk.speed = 0.4f;
		atk.loop = false;

		skill_animation_set.push_back(atk);
	}
}

void sklBasicAttack::SkillInit()
{

}

/*
//------Martial Blood
*/

// Striking Strike
sklStingingStrike::sklStingingStrike()
{
	skill_tex = App->tex->Load("textures/vamp_attack.png");
	price = 1500;
	price_dt = 200;

	cooldown = 1;
}

sklStingingStrike::~sklStingingStrike()
{
	App->tex->UnLoad(skill_tex);
}

void sklStingingStrike::SkillEffect()
{
	int damage = final_damage_down;
	damage += rand() % (final_damage_up - final_damage_down + 1);
	damage += int((float(damage) / 100) * player->dex_final);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);

	player->ChangeMP(final_blood_charge_increase);
	player->TakeDamage(final_life_cost);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;

	cooldown_timer.Start();
}

void sklStingingStrike::SkillInit()
{
	
}
void sklStingingStrike::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() == 12 && player->attacking == true)
	{
		SkillEffect();
	}
	else if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}

void sklStingingStrike::SetSkillAnimations()
{
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 20, SPRITE_MARGIN);
		atk.speed = 0.4f;
		atk.loop = false;

		skill_animation_set.push_back(atk);
	}
}

void sklStingingStrike::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;
	
	final_life_cost = life_cost_base + life_cost_dt * level;

	final_blood_charge_increase = blood_charge_increase_base + blood_dt * level;
}

//Wild Talon
sklWildTalon::sklWildTalon()
{
	skill_tex = App->tex->Load("textures/vamp_kick.png");
	price = 1500;
	price_dt = 200;

	cooldown = 2;
}
sklWildTalon::~sklWildTalon()
{
	App->tex->UnLoad(skill_tex);
}

void sklWildTalon::SkillEffect()
{
	float damage = final_damage_down;
	damage += rand() % (final_damage_up - final_damage_down + 1);
	damage += float((float(damage) / 100) * player->dex_final);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);
	player->ChangeMP(blood_charge_increase_base);
	player->RestoreHP(-life_cost_final);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;

	cooldown_timer.Start();
}

void sklWildTalon::SkillInit()
{

}

void sklWildTalon::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() == 5 && player->attacking == true)
	{
		SkillEffect();
	}
	else if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}
void sklWildTalon::SetSkillAnimations()
{
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		atk.speed = 0.4f;
		atk.loop = false;

		skill_animation_set.push_back(atk);
	}
}

void sklWildTalon::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	life_cost_final = life_cost_base + life_cost_dt * level;

	final_blood_charge_increase = blood_charge_increase_base + blood_dt * level;
}

//Bat Strike
sklBatStrike::sklBatStrike()
{
	skill_tex = App->tex->Load("textures/vamp_attack.png");
	price = 2500;
	price_dt = 200;

	cooldown = 3;
}
sklBatStrike::~sklBatStrike()
{
	App->tex->UnLoad(skill_tex);
}

void sklBatStrike::SkillEffect()
{
	float damage = final_damage_down;
	
	if (player->MP_current >= blood_charge_cost_final)
	{
		damage += rand() % (final_damage_up - final_damage_down + 1);
		damage += float((float(damage) / 100) * player->dex_final);
		player->RestoreHP(float((damage) / 100)*life_steal);
	}

	player->enemy->TakeDamage(damage);

	//App->audio->PlayFx(player_attack, 0);
	player->ChangeMP(-blood_charge_cost_final);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;


	cooldown_timer.Start();
}

void sklBatStrike::SkillInit()
{

}
void sklBatStrike::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() == 12 && player->attacking == true)
	{
		if (player->MP_current >= blood_charge_cost_final)
		{
			iPoint pos;
			pos.x = player->enemy->position.x;
			pos.y = player->enemy->position.y + 1;
			particle_skill = App->pm->AddParticle(player->effect_red, pos.x, pos.y, 1, player->effect_red.image);
		}
			
		SkillEffect();
	}
	else if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}
void sklBatStrike::SetSkillAnimations()
{
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 20, SPRITE_MARGIN);
		atk.speed = 0.4f;
		atk.loop = false;

		skill_animation_set.push_back(atk);
	}
}

void sklBatStrike::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;
}

//Soul of Ice
sklSoulOfIce::sklSoulOfIce()
{
	skill_tex = App->tex->Load("textures/vamp_kick.png");
	price = 2500;
	price_dt = 200;

	cooldown = 3;
}
sklSoulOfIce::~sklSoulOfIce()
{
	App->tex->UnLoad(skill_tex);
}

void sklSoulOfIce::SkillEffect()
{
	float damage = final_damage_down;

	if (player->MP_current >= blood_charge_cost_final)
	{
		damage += rand() % (final_damage_up - final_damage_down + 1);
		damage += float((float(damage) / 100) * player->dex_final);
		player->enemy->Freeze(3);
	}

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);
	player->ChangeMP(-blood_charge_cost_final);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;


	cooldown_timer.Start();
}

void sklSoulOfIce::SkillInit()
{

}
void sklSoulOfIce::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() == 5 && player->attacking == true)
	{
		if (player->MP_current >= blood_charge_cost_final)
		{
			iPoint pos;
			pos.x = player->enemy->position.x;
			pos.y = player->enemy->position.y + 1;
			particle_skill = App->pm->AddParticle(player->effect_blue, pos.x, pos.y, 1, player->effect_blue.image);
		}
			
		SkillEffect();
	}

	else if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}
void sklSoulOfIce::SetSkillAnimations()
{
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		atk.speed = 0.4f;
		atk.loop = false;

		skill_animation_set.push_back(atk);
	}
}

void sklSoulOfIce::CalculateSkillStats()
{
	
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;
}

//Krobus Arts 
//NOTE: for now, it's acting as a temporal buff
sklKrobusArts::sklKrobusArts() :sklBuff(EXTRA_DAMAGE, 45, 10)
{
	price = 2000;
	price_dt = 200;

	cooldown = 10;

	skill_tex = App->tex->Load("textures/vamp_cast.png");
}

sklKrobusArts::~sklKrobusArts()
{
	App->tex->UnLoad(skill_tex);
}

void sklKrobusArts::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();

	player->attacking = false;

	cooldown_timer.Start();
}

void sklKrobusArts::SkillInit()
{
	player->attacking = true;

	player->RestoreHP(-life_cost_final);
}

void sklKrobusArts::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		SkillEffect();
		buff_particle = App->pm->AddParticle(player->green_buff_1, player->p_position.x, player->p_position.y + 2, buff.time, player->green_buff_1.image);
	}

	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->attacking = false;
	}
}

void sklKrobusArts::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklKrobusArts::CalculateSkillStats()
{
	damage_bonus_final = damage_bonus_base + damage_bonus_dt * level;

	life_cost_final = life_cost_base + life_cost_dt * level;

	buff.value = damage_bonus_final;
}
//Blood Arrow
//NOTE: change this to be aplicable with the system particle
sklBloodArrow::sklBloodArrow() : sklRanged()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 1500;
	price_dt = 200;

	cooldown = 1.5f;
}

sklBloodArrow::~sklBloodArrow()
{
	App->tex->UnLoad(skill_tex);
}

void sklBloodArrow::SkillEffect()
{}

void sklBloodArrow::SkillInit()
{
	player->particle_destination.x = App->input->GetMouseWorldPosition().x;
	player->particle_destination.y = App->input->GetMouseWorldPosition().y;
	player->SetDirection(player->particle_destination);


	player->RestoreHP(-life_cost_final);

	cooldown_timer.Start();
}

void sklBloodArrow::SkillUpdate(float dt)
{
	//NOTE: provisional
	player->SetDirection(player->particle_destination);

	if (player->current_animation->CurrentFrame() >= 7 && !player->particle_is_casted)
	{
		float damage = final_damage_down;
		damage += rand() % (final_damage_up - final_damage_down + 1);
		damage += float((float(damage) / 100) * player->int_final);

		skill_particle = App->pm->AddParticle(player->particle_skill_1, player->p_position.x, player->p_position.y - 40, 2, player->particle_skill_1.image);
		player->particle_is_casted = true;
		skill_particle->damage = damage;
		skill_particle->SetPointSpeed(150, player->particle_destination);
	}

	if (player->current_animation->Finished())
	{
		player->ChangeMP(blood_charge_increase_final);
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->particle_is_casted = false;
	}

}

void sklBloodArrow::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklBloodArrow::CalculateSkillStats()
{	
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	life_cost_final = life_cost_base + life_cost_dt * level;

	blood_charge_increase_final = blood_charge_increase_base + blood_charge_increase_dt * level;
}

//Vampire Breath
sklVampireBreath::sklVampireBreath()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 1500;
	price_dt = 200;

	cooldown = 9;
}
sklVampireBreath::~sklVampireBreath()
{
	App->tex->UnLoad(skill_tex);
}

void sklVampireBreath::SkillEffect(float dt)
{
	iPoint pos = { int(player->p_position.x), int(player->p_position.y) };

	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, range);

	float damage = final_damage_down;
	damage += rand() % (final_damage_up - final_damage_down + 1);
	damage += int((float(damage) / 100) * player->int_final);
	damage = float(damage) * dt;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage(damage);
	}

	App->render->DrawCircle(pos.x, pos.y, range, 255, 0, 0);
}

void sklVampireBreath::SkillInit()
{
	iPoint pos = App->input->GetMouseWorldPosition();
	direction = player->p_position.GetDirection({ float(pos.x), float(pos.y) });

	if (player->MP_current > blood_charge_cost_base)
	{
		skill_particle_up = App->pm->AddParticle(player->area_3_up, player->p_position.x, player->p_position.y + 5, 5, player->area_3_up.image);
		skill_particle_up->FollowPoint(player->p_position.x, player->p_position.y + 5 - skill_particle_up->anim.PeekCurrentFrame().h / 2);
		skill_particle_down = App->pm->AddParticle(player->area_3_down, player->p_position.x, player->p_position.y + 5, 5, player->area_3_down.image);
		skill_particle_down->FollowPoint(player->p_position.x, player->p_position.y + 5 + skill_particle_up->anim.PeekCurrentFrame().h / 2);
	}

	cooldown_timer.Start();
}

void sklVampireBreath::SkillUpdate(float dt)
{
	if (player->MP_current > 0)
	{
		SkillEffect(dt);

		player->MP_current -= blood_charge_cost_base * dt;
		player->PlayerEvent(MP_DOWN);

	}
	else
	{
		if (skill_particle_up != NULL)
			skill_particle_up->DestroyParticle();

		if (skill_particle_down != NULL)
			skill_particle_down->DestroyParticle();

		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;

	}
}

void sklVampireBreath::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		//cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklVampireBreath::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;
}

//BloodBomb
sklBloodBomb::sklBloodBomb()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");

	price = 2500;
	price_dt = 200;

	cooldown = 3;
}

sklBloodBomb::~sklBloodBomb()
{
	App->tex->UnLoad(skill_tex);
}

void sklBloodBomb::SkillEffect()
{
	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->particle_is_casted = false;
	}
}

void sklBloodBomb::SkillInit()
{
	player->particle_destination.x = App->input->GetMouseWorldPosition().x;
	player->particle_destination.y = App->input->GetMouseWorldPosition().y;
	player->SetDirection(player->particle_destination);

	player->TakeDamage(life_cost_base);

	cooldown_timer.Start();
}

void sklBloodBomb::SkillIndependentUpdate(float dt)
{

}

void sklBloodBomb::SkillUpdate(float dt)
{
	player->SetDirection(player->particle_destination);

	if (player->current_animation->CurrentFrame() >= 7 && !player->particle_is_casted)
	{
		float damage = final_damage_down;
		damage += rand() % (final_damage_up - final_damage_down + 1);
		damage += float((float(damage) / 100) * player->int_final);

		skill_particle = App->pm->AddParticle(player->particle_skill_2, player->p_position.x, player->p_position.y - 40, 2, player->particle_skill_2.image);
		player->particle_is_casted = true;
		skill_particle->damage = damage;
		skill_particle->SetPointSpeed(150, player->particle_destination);
	}

	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->particle_is_casted = false;
	}
}
void sklBloodBomb::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklBloodBomb::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	life_cost_final = life_cost_base + life_cost_dt * level;

	blood_charge_increase_final = blood_charge_increase_base + blood_charge_increase_dt * level;
}

//Red Feast
sklRedFeast::sklRedFeast()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 2500;
	price_dt = 200;

	cooldown = 10;
}
sklRedFeast::~sklRedFeast()
{
	App->tex->UnLoad(skill_tex);
}

void sklRedFeast::SkillEffect(float dt)
{
	iPoint pos = {int(player->p_position.x), int(player->p_position.y)};

	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, radius);

	float damage = final_damage_down;
	damage += rand() % (final_damage_up - final_damage_down + 1);
	damage += int((float(damage) / 100) * player->int_final);
	damage = float(damage) * dt;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage(damage);
		enemies[i]->Freeze(1);
		hit = true;
	}

	if (hit)
	{
		float stealed_life = (damage / 100) * life_steal_base;
		player->TakeDamage(-stealed_life);
	}

	App->render->DrawCircle(pos.x, pos.y, radius, 255, 0, 0);
}

void sklRedFeast::SkillInit()
{
	hit = false;

	if (player->MP_current > blood_charge_cost_base)
	{
		skill_particle_up = App->pm->AddParticle(player->area_2_up, player->p_position.x, player->p_position.y + 5, 5, player->area_2_up.image);
		skill_particle_up->FollowPoint(player->p_position.x, player->p_position.y + 5 - skill_particle_up->anim.PeekCurrentFrame().h / 2);
		skill_particle_down = App->pm->AddParticle(player->area_2_down, player->p_position.x, player->p_position.y + 5, 5, player->area_2_down.image);
		skill_particle_down->FollowPoint(player->p_position.x, player->p_position.y + 5 + skill_particle_up->anim.PeekCurrentFrame().h / 2);
	}

	cooldown_timer.Start();
}

void sklRedFeast::SkillUpdate(float dt)
{
	if (player->MP_current > 0)
	{
		SkillEffect(dt);

		player->MP_current -= blood_charge_cost_base * dt;
		player->PlayerEvent(MP_DOWN);
	}
	else
	{
		if (skill_particle_up != NULL)
			skill_particle_up->DestroyParticle();

		if (skill_particle_down != NULL)
			skill_particle_down->DestroyParticle();

		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
	}
}

void sklRedFeast::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		//cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklRedFeast::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;
}

//Heard of Bats
sklHeardOfBats::sklHeardOfBats()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 2000;
	price_dt = 200;

	cooldown = 8;
}
sklHeardOfBats::~sklHeardOfBats()
{
	App->tex->UnLoad(skill_tex);
}

void sklHeardOfBats::SkillEffect(float dt)
{
	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, radius);

	float damage = final_damage_down;
	damage += rand() % (final_damage_up - final_damage_down + 1);
	damage += int((float(damage) / 100) * player->int_final);
	damage = float(damage) * dt;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage(damage);
		hit = true;
	}

	App->render->DrawCircle(pos.x, pos.y, radius, 255, 0, 0);

}

void sklHeardOfBats::SkillInit()
{
	pos = App->input->GetMouseWorldPosition();
	player->independent_skill = this;
	hit = false;

	if (player->MP_current > blood_charge_increase_base)
	{
		Particle* skill_particle_up = App->pm->AddParticle(player->area_1_up, pos.x, pos.y, time, player->area_1_up.image);
		skill_particle_up->FollowPoint(pos.x, pos.y - skill_particle_up->anim.PeekCurrentFrame().h / 2);
		Particle* skill_particle_down = App->pm->AddParticle(player->area_1_down, pos.x, pos.y, time, player->area_1_down.image);
		skill_particle_down->FollowPoint(pos.x, pos.y + skill_particle_up->anim.PeekCurrentFrame().h / 2);
	}
	
	player->ChangeMP(-blood_charge_cost_final);

	timer.Start();
	cooldown_timer.Start();
}

void sklHeardOfBats::SkillIndependentUpdate(float dt)
{
	if (player->MP_current > 0 && timer.ReadSec() < time)
	{
		SkillEffect(dt);
	}
	else
	{
		player->independent_skill = NULL;

		if (hit)
		{
			player->ChangeMP(-blood_charge_cost_final);
		}
	}
}

void sklHeardOfBats::SkillUpdate(float dt)
{
	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
	}	
}

void sklHeardOfBats::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklHeardOfBats::CalculateSkillStats()
{
	final_damage_down = base_damage_down + damage_down_dt * level;
	final_damage_up = base_damage_up + damage_up_dt * level;

	blood_charge_cost_final = blood_charge_increase_base + blood_charge_cost_dt * level;
}

//Night Passives
sklShadowsWalker::sklShadowsWalker() : sklBuff(INVISIBILITY, 1, 5) //We should put a "time_effect_final" variable instead of "5"
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 1500;
	price_dt = 200;

	cooldown = 10;
}

sklShadowsWalker::~sklShadowsWalker()
{
	App->tex->UnLoad(skill_tex);
}

void sklShadowsWalker::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();
	player->ChangeMP(-blood_charge_cost_final);

	player->attacking = false;
}

void sklShadowsWalker::SkillInit()
{
	player->attacking = true;
	cooldown_timer.Start();
}
void sklShadowsWalker::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		if (player->MP_current >= blood_charge_cost_final)
		{
			SkillEffect();
			buff_particle = App->pm->AddParticle(player->white_buff_1, player->p_position.x, player->p_position.y + 2, buff.time, player->white_buff_1.image);
		}
	}

	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->attacking = false;
	}
}
void sklShadowsWalker::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklShadowsWalker::CalculateSkillStats()
{
	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;

	time_effect_final = time_effect_base + time_effect_dt * level;
}

//Clotted blood skin
sklClottedBloodSkin::sklClottedBloodSkin() : sklBuff(ARMOR, 10, 3) //We should put a "buff_armor_final" variable instead of "10"
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	price = 2000;
	price_dt = 200;

	cooldown= 13;
}

sklClottedBloodSkin::~sklClottedBloodSkin()
{
	App->tex->UnLoad(skill_tex);
}

void sklClottedBloodSkin::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();
	player->ChangeMP(-blood_charge_cost_final);

	player->attacking = false;
}

void sklClottedBloodSkin::SkillInit()
{
	player->attacking = true;
	cooldown_timer.Start();
}
void sklClottedBloodSkin::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		if (player->MP_current >= blood_charge_cost_final)
		{
			SkillEffect();
			buff_particle = App->pm->AddParticle(player->red_buff_1, player->p_position.x, player->p_position.y + 2, buff.time, player->red_buff_1.image);
		}
	}

	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->input_locked = false;
		player->attacking = false;
	}
}
void sklClottedBloodSkin::SetSkillAnimations()
{
	for (int i = 0; i < 12; i++)
	{
		Animation cst;
		cst.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 12, SPRITE_MARGIN);
		cst.speed = 0.3f;
		cst.loop = false;

		skill_animation_set.push_back(cst);
	}
}

void sklClottedBloodSkin::CalculateSkillStats()
{
	blood_charge_cost_final = blood_charge_cost_base + blood_charge_cost_dt * level;

	buff_armor_final = buff_armor_base + buff_armor_dt * level;
}

//Lust
sklLust::sklLust()
{
	price = 1500;
	price_dt = 200;
}

sklLust::~sklLust()
{

}


void sklLust::SkillEffect()
{
	player->CalculateFinalStats();
}

void sklLust::SkillInit()
{
	player->CalculateFinalStats();
}

void sklLust::CalculateSkillStats()
{
	basic_blood_charges = basic_blood_charges_base + basic_blood_charges_dt * level;
	
	increased_HP = increased_HP_base + increased_HP_dt * level;
}

//Undead
sklUndead::sklUndead()
{
	avaliable = true;
	price = 2500;
	price_dt = 200;

	cooldown = 60;
}

sklUndead::~sklUndead()
{

}

void sklUndead::SkillEffect()
{
	player->inmune = true;
	active = true;
	avaliable = false;
	effect_timer.Start();
	player->CalculateFinalStats();
	buff_particle = App->pm->AddParticle(player->blue_buff_1, player->p_position.x, player->p_position.y + 2, 4, player->blue_buff_1.image);
}

void sklUndead::SkillInit()
{
	/*if (avaliable)
	{
		SkillEffect();
	}*/
}
void sklUndead::SkillUpdate(float dt)
{
	if (active)
	{
		if (effect_timer.ReadSec() >= time)
		{
			active = false;
			player->inmune = false;
			player->CalculateFinalStats();
			cooldown_timer.Start();
		}
	}
	else
	{
		float sec = cooldown_timer.ReadSec();
		if (sec >= cooldown)
		{
			avaliable = true;
		}
	}
}

void sklUndead::CalculateSkillStats()
{
	life_steal = life_steal_base + life_steal_dt * level;

	extra_damage = extra_damage_base + extra_damage_dt * level;
}

//Night ward
sklNightWard::sklNightWard()
{
	price = 2000;
	price_dt = 200;

	cooldown = 10;
}
sklNightWard::~sklNightWard()
{

}

void sklNightWard::SkillEffect()
{
	active = false;
	avaliable = false;
	cooldown_timer.Start();
}

void sklNightWard::SkillInit()
{
	effect_timer.Start();
	//buff_particle = App->pm->AddParticle(player->yellow_buff_1, player->p_position.x, player->p_position.y + 2, 60, player->yellow_buff_1.image);
}

void sklNightWard::SkillUpdate(float dt)
{
	if (avaliable)
	{
		if (effect_timer.ReadSec() >= time)
		{
			active = true;
		}
	}

	else
	{
		if (cooldown_timer.ReadSec() >= cooldown)
		{
			avaliable = true;
			SkillInit();
		}
	}

	if (active && buff_particle != NULL)
	{
		buff_particle->DestroyParticle();
		buff_particle = NULL;
	}

}

void sklNightWard::CalculateSkillStats()
{
	damage_reduction_final = damage_reduction_base + damage_reduction_dt * level;
}
