#ifndef _SKILL_H_
#define _SKILL_H_

#include <vector>
#include "Animation.h"

struct SDL_Texture;
class j1Player;

enum SKILL_TYPE
{
	SKILL_MELEE,
	SKILL_RANGED,
	SKILL_AREA,
	SKILL_SUMMON,
	SKILL_BUFF
};

class Skill
{
public:
	Skill(SKILL_TYPE t);

	virtual ~Skill()
	{}

	virtual void SkillEffect()
	{}

	virtual void SkillInit()
	{}
	virtual void SkillUpdate()
	{}
	virtual void SetSkillAnimations()
	{}

public:

	SKILL_TYPE skill_type;
	SDL_Texture* skill_tex;
	vector<Animation> skill_animation_set;
	j1Player* player;
};

class sklMelee : public Skill
{
public:
	sklMelee() : Skill(SKILL_MELEE)
	{}

	virtual ~sklMelee()
	{}

public:

	float range;
};

class sklRanged : public Skill
{
public:
	sklRanged() : Skill(SKILL_RANGED)
	{}

	virtual ~sklRanged()
	{}

public:

	float speed;

};


class sklArea : public Skill
{
public:
	sklArea() : Skill(SKILL_AREA)
	{}

	virtual ~sklArea()
	{}


public:

	float range;
};

class sklBuff : public Skill
{
public:
	sklBuff() : Skill(SKILL_BUFF)
	{}

	virtual ~sklBuff()
	{}


public:

};

//NOTE: this is the tricky one
class sklSummon : public Skill
{
public: 
	sklSummon() :Skill(SKILL_SUMMON)
	{}

	virtual ~sklSummon()
	{}


public:

};

//Passive skill?


#endif _SKILL_H_