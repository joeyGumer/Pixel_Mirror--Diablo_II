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

void sklKrobusArts::SkillUpdate()
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

//Vampire Breath
sklVampireBreath::sklVampireBreath()
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklVampireBreath::~sklVampireBreath()
{

}

void sklVampireBreath::SkillEffect()
{

}

void sklVampireBreath::SkillInit()
{

}
void sklVampireBreath::SkillUpdate()
{

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

}

void sklBloodBomb::SkillInit()
{

}
void sklBloodBomb::SkillUpdate()
{

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
}
sklRedFeast::~sklRedFeast()
{

}

void sklRedFeast::SkillEffect()
{

}

void sklRedFeast::SkillInit()
{

}

void sklRedFeast::SkillUpdate()
{

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
}
sklHeardOfBats::~sklHeardOfBats()
{

}

void sklHeardOfBats::SkillEffect()
{

}

void sklHeardOfBats::SkillInit()
{

}
void sklHeardOfBats::SkillUpdate()
{

}
void sklHeardOfBats::SetSkillAnimations()
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




//Night Passives
sklShadowsWalker::sklShadowsWalker() : sklBuff(STRENGHT, 1, 1)
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklShadowsWalker::~sklShadowsWalker()
{

}

void sklShadowsWalker::SkillEffect()
{

}

void sklShadowsWalker::SkillInit()
{

}
void sklShadowsWalker::SkillUpdate()
{

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
sklClottedBloodSkin::sklClottedBloodSkin() : sklBuff(STRENGHT, 1, 1)
{
	skill_tex = App->tex->Load("textures/vamp_cast.png");
}
sklClottedBloodSkin::~sklClottedBloodSkin()
{

}

void sklClottedBloodSkin::SkillEffect()
{

}

void sklClottedBloodSkin::SkillInit()
{

}
void sklClottedBloodSkin::SkillUpdate()
{

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
