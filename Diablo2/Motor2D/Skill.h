#ifndef _SKILL_H_
#define _SKILL_H_

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
	Skill(SKILL_TYPE t) : type(t)
	{}

	virtual ~Skill();

	virtual void Effect();

public:

	SKILL_TYPE type;
};

class sklMelee : public Skill
{
public:
	sklMelee() : Skill(SKILL_MELEE)
	{}

	virtual ~sklMelee();

	virtual void Effect();

public:

	float range;

};

class sklRanged : public Skill
{
public:
	sklRanged() : Skill(SKILL_RANGED)
	{}

	virtual ~sklRanged();

	virtual void Effect();

public:

	float speed;

};


class sklArea : public Skill
{
public:
	sklArea() : Skill(SKILL_AREA)
	{}

	virtual ~sklArea();

	virtual void Effect();

public:

	float range;
};

class sklBuff : public Skill
{
public:
	sklBuff() : Skill(SKILL_BUFF)
	{}

	virtual ~sklBuff();

	virtual void Effect();

public:

};

//NOTE: this is the tricky one
class sklSummon : public Skill
{
public: 
	sklSummon() :Skill(SKILL_SUMMON)
	{}

	virtual ~sklSummon();

	virtual void Effect();
public:

};


#endif _SKILL_H_