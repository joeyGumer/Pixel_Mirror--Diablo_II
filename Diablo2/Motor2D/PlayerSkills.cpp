#include "PlayerSkills.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Game.h"
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

void sklBasicAttack::SkillUpdate()
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
void sklStingingStrike::SkillUpdate()
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

void sklWildTalon::SkillUpdate()
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
void sklBatStrike::SkillUpdate()
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
void sklSoulOfIce::SkillUpdate()
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

void sklBloodArrow::SkillUpdate()
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