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

	player->enemy->TakeDamage(player->atk_damage_final);

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

	base_damage_down = 13;
	base_damage_up = 17;
}

sklStingingStrike::~sklStingingStrike()
{

}

void sklStingingStrike::SkillEffect()
{
	int damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;
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

//Wild Talon
sklWildTalon::sklWildTalon()
{
	skill_tex = App->tex->Load("textures/vamp_attack.png");

	base_damage_down = 21;
	base_damage_up = 32;
}
sklWildTalon::~sklWildTalon()
{

}

void sklWildTalon::SkillEffect()
{
	int damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;
}

void sklWildTalon::SkillInit()
{

}

void sklWildTalon::SkillUpdate(float dt)
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
void sklWildTalon::SetSkillAnimations()
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
//Bat Strike
sklBatStrike::sklBatStrike()
{
	skill_tex = App->tex->Load("textures/vamp_attack.png");

	base_damage_down = 21;
	base_damage_up = 32;
}
sklBatStrike::~sklBatStrike()
{

}

void sklBatStrike::SkillEffect()
{
	int damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;
}

void sklBatStrike::SkillInit()
{

}
void sklBatStrike::SkillUpdate(float dt)
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

//Soul of Ice
sklSoulOfIce::sklSoulOfIce()
{
	skill_tex = App->tex->Load("textures/vamp_attack.png");

	base_damage_down = 21;
	base_damage_up = 32;
}
sklSoulOfIce::~sklSoulOfIce()
{

}

void sklSoulOfIce::SkillEffect()
{
	int damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);

	player->enemy->TakeDamage(damage);
	//App->audio->PlayFx(player_attack, 0);

	player->enemy = NULL;
	player->objective = NULL;
	player->attacking = false;
}

void sklSoulOfIce::SkillInit()
{

}
void sklSoulOfIce::SkillUpdate(float dt)
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
void sklSoulOfIce::SetSkillAnimations()
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

//Krobus Arts 
//NOTE: for now, it's acting as a temporal buff
sklKrobusArts::sklKrobusArts() :sklBuff(EXTRA_DAMAGE, 45, 15)
{
	damage_bonus_base = 45;
	damage_bonus_dt = 10;

	skill_tex = App->tex->Load("textures/vamp_cast.png");
}

sklKrobusArts::~sklKrobusArts()
{

}

void sklKrobusArts::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();

	player->attacking = false;
}

void sklKrobusArts::SkillInit()
{
	player->attacking = true;
}

void sklKrobusArts::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		SkillEffect();
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
//Blood Arrow
//NOTE: change this to be aplicable with the system particle
sklBloodArrow::sklBloodArrow() : sklRanged()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}

sklBloodArrow::~sklBloodArrow()
{}

void sklBloodArrow::SkillEffect()
{}

void sklBloodArrow::SkillInit()
{
	player->particle_destination.x = App->input->GetMouseWorldPosition().x;
	player->particle_destination.y = App->input->GetMouseWorldPosition().y;
	player->SetDirection(player->particle_destination);
}

void sklBloodArrow::SkillUpdate(float dt)
{
	//NOTE: provisional
	player->SetDirection(player->particle_destination);

	if (player->current_animation->CurrentFrame() >= 7 && !player->particle_is_casted)
	{
		skill_particle = App->pm->AddParticle(player->particle_skill_1, player->p_position.x, player->p_position.y - 40, 2, player->particle_skill_1.image);
		player->particle_is_casted = true;
		skill_particle->SetPointSpeed(150, player->particle_destination);
	}

	if (player->current_animation->Finished())
	{
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

//Vampire Breath
sklVampireBreath::sklVampireBreath()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
	range = 150;
	base_damage_down = 12;
	base_damage_up = 25;
	radius = 50;

}
sklVampireBreath::~sklVampireBreath()
{
	
}

void sklVampireBreath::SkillEffect(float dt)
{
	iPoint pos = { int(player->p_position.x), int(player->p_position.y) };

	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, radius);

	float damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);
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


}
void sklVampireBreath::SkillUpdate(float dt)
{
	if (player->MP_current > 0)
	{
		SkillEffect(dt);

		player->MP_current -= 20.0f * dt;
		player->PlayerEvent(MP_DOWN);

	}
	else
	{

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

//BloodBomb
sklBloodBomb::sklBloodBomb()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklBloodBomb::~sklBloodBomb()
{

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
}

void sklBloodBomb::SkillIndependentUpdate(float dt)
{

}

void sklBloodBomb::SkillUpdate(float dt)
{
	player->SetDirection(player->particle_destination);

	if (player->current_animation->CurrentFrame() >= 7 && !player->particle_is_casted)
	{
		skill_particle = App->pm->AddParticle(player->particle_skill_1, player->p_position.x, player->p_position.y - 40, 2, player->particle_skill_1.image);
		player->particle_is_casted = true;
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

//Red Feast
sklRedFeast::sklRedFeast()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");

	base_damage_down = 4;
	base_damage_up = 10;

	radius = 200;
}
sklRedFeast::~sklRedFeast()
{

}

void sklRedFeast::SkillEffect(float dt)
{
	iPoint pos = {int(player->p_position.x), int(player->p_position.y)};

	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, radius);

	float damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);
	damage = float(damage) * dt;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage(damage);
	}

	App->render->DrawCircle(pos.x, pos.y, radius, 255, 0, 0);
}

void sklRedFeast::SkillInit()
{

}

void sklRedFeast::SkillUpdate(float dt)
{
	if (player->MP_current > 0)
	{
		SkillEffect(dt);

		player->MP_current -= 20.0f * dt;
		player->PlayerEvent(MP_DOWN);

	}
	else
	{

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



sklHeardOfBats::sklHeardOfBats()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");

	time = 5;
	radius = 150;
	base_damage_down = 4;
	base_damage_up = 10;
}
sklHeardOfBats::~sklHeardOfBats()
{

}

void sklHeardOfBats::SkillEffect(float dt)
{
	

	vector<EntEnemy*> enemies = App->game->em->EnemiesOnArea(pos, radius);

	float damage = base_damage_down;
	damage += rand() % (base_damage_up - base_damage_down + 1);
	damage = float(damage) * dt;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage(damage);
	}

	App->render->DrawCircle(pos.x, pos.y, radius, 255, 0, 0);

}

void sklHeardOfBats::SkillInit()
{
	pos = App->input->GetMouseWorldPosition();
	player->independent_skill = this;

	timer.Start();
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




//Night Passives
sklShadowsWalker::sklShadowsWalker() : sklBuff(INVISIBILITY, 1, 30)
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklShadowsWalker::~sklShadowsWalker()
{

}

void sklShadowsWalker::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();

	player->attacking = false;
}

void sklShadowsWalker::SkillInit()
{
	player->attacking = true;
}
void sklShadowsWalker::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		SkillEffect();
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

//Clotted blood skin
sklClottedBloodSkin::sklClottedBloodSkin() : sklBuff(ARMOR, 20, 3)
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklClottedBloodSkin::~sklClottedBloodSkin()
{

}

void sklClottedBloodSkin::SkillEffect()
{
	Buff* tmp_buff;
	tmp_buff = new Buff(buff.attribute, buff.value, false, buff.time);

	player->buffs.push_back(tmp_buff);
	player->CalculateFinalStats();

	player->attacking = false;
}

void sklClottedBloodSkin::SkillInit()
{
	player->attacking = true;
}
void sklClottedBloodSkin::SkillUpdate(float dt)
{
	if (player->current_animation->CurrentFrame() >= 7 && player->attacking == true)
	{
		SkillEffect();
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
