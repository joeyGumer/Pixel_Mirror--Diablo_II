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
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int life_cost_base = 4;
	int life_cost_dt = 1;
	int final_life_cost = life_cost_base;

	int blood_charge_increase_base = 5;
	int blood_dt = 1;
	int final_blood_charge_increase = blood_charge_increase_base;

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

	void CalculateSkillStats();

public:

	int base_damage_down = 17;
	int base_damage_up = 24;
	int damage_down_dt = 8;
	int damage_up_dt = 9;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_increase_base = 10;
	int blood_dt = 1;
	int final_blood_charge_increase = blood_charge_increase_base;

	int life_cost_base = 6;
	int life_cost_dt = 2;
	int life_cost_final = life_cost_base;
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

	void CalculateSkillStats();

public:

	Particle* particle_skill = NULL;

	int base_damage_down = 13;
	int base_damage_up = 17;
	int damage_down_dt = 7;
	int damage_up_dt = 8;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_cost_base = 10;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;

	int life_steal = 50;
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

	void CalculateSkillStats();

public:

	Particle* particle_skill = NULL;

	int base_damage_down = 17;
	int base_damage_up = 24;
	int damage_down_dt  = 8;
	int damage_up_dt = 9;
	int final_damage_down =base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_cost_base = 10;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;
	
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

	void CalculateSkillStats();
public:

	int damage_bonus_base = 45;
	int damage_bonus_dt = 10;
	int damage_bonus_final = damage_bonus_base;

	int life_cost_base = 7;
	int life_cost_dt = 2;
	int life_cost_final = life_cost_base;

	Particle* buff_particle = NULL;
	
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
	void CalculateSkillStats();

public:
	Particle* skill_particle;

	int base_damage_down = 8;
	int base_damage_up = 12;
	int damage_down_dt = 4;
	int damage_up_dt = 5;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int life_cost_base = 4;
	int life_cost_dt = 1;
	int life_cost_final = life_cost_base;

	int blood_charge_increase_base = 7;
	int blood_charge_increase_dt = 1;
	int blood_charge_increase_final = blood_charge_increase_base;
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
	void CalculateSkillStats();

public:
	

	Particle* skill_particle_up;
	Particle* skill_particle_down;

	int base_damage_down = 12;
	int base_damage_up = 18;
	int damage_down_dt = 8;
	int damage_up_dt = 9;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_cost_base = 15;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;

	float radius = 50;
	int range = 150;

	float direction;
	//float cooldown_base;
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
	void CalculateSkillStats();

public:
	Particle* skill_particle;

	int base_damage_down = 12;
	int base_damage_up = 18;
	int damage_down_dt = 8;
	int damage_up_dt = 9;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int life_cost_base = 8;
	int life_cost_dt = 2;
	int life_cost_final = life_cost_base;

	int blood_charge_increase_base = 12;
	int blood_charge_increase_dt = 1;
	int blood_charge_increase_final = blood_charge_increase_base;
	//float cooldown_base;
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
	void CalculateSkillStats();

public:
	//Particle* skill_particle;

	Particle* skill_particle_up;
	Particle* skill_particle_down;
	//

	int base_damage_down = 8;
	int base_damage_up = 14;
	int damage_down_dt = 8;
	int damage_up_dt = 9;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_cost_base = 14;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;

	int radius = 200;

	int life_steal_base = 50;

	int time;
	//float cooldown_base;
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
	void CalculateSkillStats();

public:
	
	int base_damage_down = 6;
	int base_damage_up = 12;
	int damage_down_dt = 10;
	int damage_up_dt = 11;
	int final_damage_down = base_damage_down;
	int final_damage_up = base_damage_up;

	int blood_charge_increase_base = 24;
	//int blood_charge_cost_base = 24;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_increase_base;

	int radius = 150;
	float direction;
	//float cooldown_base;

	int time = 3;
	iPoint pos;
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
	void CalculateSkillStats();

public:
	int time;
	//float cooldown_base;

	Particle* buff_particle = NULL;

	int blood_charge_cost_base = 20;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;

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
	void CalculateSkillStats();

public:
	//float cooldown_base;

	Particle* buff_particle = NULL;

	int blood_charge_cost_base = 26;
	int blood_charge_cost_dt = 2;
	int blood_charge_cost_final = blood_charge_cost_base;

	int buff_armor_base = 10;
	int buff_armor_dt = 2;
	int buff_armor_final = buff_armor_base;

};

class sklLust : public sklPassive
{
public:
	sklLust();
	~sklLust();

	void SkillEffect();
	void SkillInit();
	void CalculateSkillStats();

public:
	int basic_blood_charges_base = 2;
	int basic_blood_charges_dt = 1;
	int basic_blood_charges = basic_blood_charges_base;

	int increased_HP_base = 5;
	int increased_HP_dt = 5;
	int increased_HP = increased_HP_base;
};

class sklUndead : public sklPassive
{
public:
	sklUndead();
	~sklUndead();

	void SkillEffect();
	void SkillInit();
	void SkillUpdate(float dt);
	void CalculateSkillStats();

public:

	int life_steal_base = 10;
	int life_steal_dt = 5;
	int life_steal = life_steal_base;

	int extra_damage_base = 25;
	int extra_damage_dt = 2;
	int extra_damage = extra_damage_base;

	int time = 4;
	bool active = false;

	j1Timer effect_timer;

	Particle* buff_particle = NULL;
};

class sklNightWard : public sklPassive
{
public:
	sklNightWard();
	~sklNightWard();

	void SkillEffect();
	void SkillInit();
	void SkillUpdate(float dt);
	void CalculateSkillStats();

public:

	float time = 5;
	//float cooldown = 60;

	//"damage_reduction_final" should be "damage_reduction_base"
	int damage_reduction_base = 24;
	int damage_reduction_dt = 4;
	int damage_reduction_final = damage_reduction_base;

	j1Timer effect_timer;

	bool active = false;

	Particle* buff_particle = NULL;
};


#endif _PLAYERSKILLS_H_