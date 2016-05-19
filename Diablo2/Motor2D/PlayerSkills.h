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

	void CalculateSkillStats();

public:

	int base_damage_down = 13;
	int base_damage_up = 17;
	int damage_up_dt = 8;
	int damage_down_dt = 7;
	int final_damage_down;
	int final_damage_up;

	int life_cost_base = 4;
	int life_cost_dt = 1;
	int final_life_cost;

	int blood_charge_increase_base = 5;
	int blood_dt = 1;
	int final_blood_charge_increase;

	//float cooldown_base = 1;
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

class sklLust : public sklPassive
{
public:
	sklLust();
	~sklLust();

	void SkillEffect();

	void SkillInit();

public:
	int basic_blood_charges = 2;
	int increased_HP = 5;

};

class sklUndead : public sklPassive
{
public:
	sklUndead();
	~sklUndead();

	void SkillEffect();
	void SkillInit();

	void SkillUpdate(float dt);

public:

	int life_steal = 10;
	int extra_damage = 25;
	int time = 4;
	bool active = false;

	j1Timer effect_timer;
};

class sklNightWard : public sklPassive
{
public:
	sklNightWard();
	~sklNightWard();

	void SkillEffect();

	void SkillInit();

	void SkillUpdate(float dt);

public:

	float time = 5;
	//float cooldown = 60;
	float damage_reduction_base = 24;
	j1Timer effect_timer;

	bool active = false;
};


#endif _PLAYERSKILLS_H_