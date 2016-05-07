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
	if (player->current_animation->Finished())
	{
		player->current_input = INPUT_STOP_MOVE;
		player->attacking = false;
		player->input_locked = false;
	}
}

void sklBasicAttack::SkillEffect()
{
	player->enemy->TakeDamage(player->atk_damage);
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
	//player->particle_skill_1.Enable();
}

void sklBloodArrow::SkillUpdate()
{
	//NOTE: provisional
	if (player->current_animation->CurrentFrame() >= 7 && !player->particle_is_casted)
	{
		skill_particle = App->pm->AddParticle(player->particle_skill_1, player->p_position.x, player->p_position.y - 40, 20, player->particle_skill_1.image);
		skill_particle->SetPointSpeed(5, player->particle_destination);
		player->particle_is_casted = true;

		SDL_Rect collider_pos;
		collider_pos.x = skill_particle->position.x;
		collider_pos.y = skill_particle->position.y;
		collider_pos.w = skill_particle->anim.PeekCurrentFrame().w;
		collider_pos.h = skill_particle->anim.PeekCurrentFrame().h;
		skill_particle->collider = App->collision->AddCollider(collider_pos, COLLIDER_PARTICLE, App->game->player);
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