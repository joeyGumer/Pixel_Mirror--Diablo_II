#ifndef _PLAYERSKILLS_H_
#define _PLAYERSKILLS_H_

#include "Skill.h"


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

class sklBloodArrow : public sklRanged
{
public:
	sklBloodArrow();
	~sklBloodArrow();

	void SkillEffect();

	void SkillInit();
	void SkillUpdate();
	void SetSkillAnimations();

};
#endif _PLAYERSKILLS_H_