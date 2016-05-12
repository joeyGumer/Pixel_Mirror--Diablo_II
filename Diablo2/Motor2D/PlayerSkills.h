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

};

class sklVampireBreath : public sklArea
{
public:
	sklVampireBreath();
	~sklVampireBreath();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	//Particle* skill_particle;
};


class sklBloodBomb : public sklRanged
{
public:
	sklBloodBomb();
	~sklBloodBomb();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate(float dt);
	void SetSkillAnimations();

public:
	//Particle* skill_particle;
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

};

#endif _PLAYERSKILLS_H_