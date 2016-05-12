#ifndef _PLAYERSKILLS_H_
#define _PLAYERSKILLS_H_

#include "Skill.h"
#include "j1ParticleManager.h"

class sklBasicAttack : public sklMelee
{
public:
	sklBasicAttack();
	~sklBasicAttack();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:

};

/*
//Martial Blood!
*/
class sklStingingStrike : public sklMelee
{
public:
	sklStingingStrike();
	~sklStingingStrike();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
};

class sklWildTalon : public sklMelee
{
public:
	sklWildTalon();
	~sklWildTalon();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
};

class sklBatStrike : public sklMelee
{
public:
	sklBatStrike();
	~sklBatStrike();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
};


class sklSoulOfIce : public sklMelee
{
public:
	sklSoulOfIce();
	~sklSoulOfIce();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
};
//
class sklBloodArrow : public sklRanged
{
public:
	sklBloodArrow();
	~sklBloodArrow();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

public:
	Particle* skill_particle;

};
#endif _PLAYERSKILLS_H_