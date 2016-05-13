#ifndef _PLAYERSKILLS_H_
#define _PLAYERSKILLS_H_

#include "Skill.h"
#include "j1ParticleManager.h"
#include "j1Timer.h"

class sklBasicAttack : public sklMelee
{
public:
	sklBasicAttack();
	~sklBasicAttack();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
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
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
	int life_cost_base;
	int blood_charge_increase_base;
	float cooldown_base;
};

class sklWildTalon : public sklMelee
{
public:
	sklWildTalon();
	~sklWildTalon();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
	int blood_charge_increase_base;
	int life_cost_base;
	float cooldown_base;
};

class sklBatStrike : public sklMelee
{
public:
	sklBatStrike();
	~sklBatStrike();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
	int life_cost_base;
	int blood_charge_increase_base;
	float cooldown_base;
};


class sklSoulOfIce : public sklMelee
{
public:
	sklSoulOfIce();
	~sklSoulOfIce();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
	int blood_charge_cost_base;
	float cooldown_base;
};

class sklKrobusArts : public sklBuff
{
public:
	sklKrobusArts();
	~sklKrobusArts();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();
public:

	int damage_bonus_base;
	int damage_bonus_dt;
	int life_cost_base;
	float cooldown_base;
};

//Blood Spells
class sklBloodArrow : public sklRanged
{
public:
	sklBloodArrow();
	~sklBloodArrow();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	Particle* skill_particle;

	int base_damage_down;
	int base_damage_up;
	int damage_dt;
	int life_cost_base;
	float cooldown_base;
	int blood_charge_increase_base;
};

class sklVampireBreath : public sklArea
{
public:
	sklVampireBreath();
	~sklVampireBreath();

	void SkillEffect(float dt);

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	
	float  radius;
	int range;
	float direction;
	int base_damage_down;
	int base_damage_up;
	int blood_charge_cost_base;
	float cooldown_base;
};


class sklBloodBomb : public sklRanged
{
public:
	sklBloodBomb();
	~sklBloodBomb();

	void SkillEffect();

	void SkillInit();
	void SkillIndependentUpdate(float dt);
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	Particle* skill_particle;
	int life_cost_base;
	int blood_charge_increase_base;
	float cooldown_base;
};

class sklRedFeast : public sklArea
{
public:
	sklRedFeast();
	~sklRedFeast();

	void SkillEffect(float dt);

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	//Particle* skill_particle;

	//
	int time;
	float radius;
	int base_damage_down;
	int base_damage_up;
	int life_steal_base;
	float blood_charge_cost_base;
	float cooldown_base;
	bool hit = false;
};


class sklHeardOfBats : public sklArea
{
public:
	sklHeardOfBats();
	~sklHeardOfBats();

	void SkillEffect(float dt);

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();
	void SkillIndependentUpdate(float dt);

public:
	
	int time;
	float radius;
	int base_damage_down;
	int base_damage_up;
	iPoint pos;
	float cooldown_base;
	int blood_charge_increase_base;
	bool hit = false;

	j1Timer timer;
};

//Passive
class sklShadowsWalker : public sklBuff
{
public:
	sklShadowsWalker();
	~sklShadowsWalker();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	int time;
	float cooldown_base;
	int blood_charge_cost_base;
};

class sklClottedBloodSkin : public sklBuff
{
public:
	sklClottedBloodSkin();
	~sklClottedBloodSkin();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	float cooldown_base;
	int blood_charge_cost_base;
};

#endif _PLAYERSKILLS_H_