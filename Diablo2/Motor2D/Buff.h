#ifndef _BUFF_H_
#define _BUFF_H_

#include "j1Player.h"
#include "j1Timer.h"

struct Buff
{
	Buff()
	{

	}
	Buff(PLAYER_ATTRIBUTE at, int v, bool perm = true, float tim = 0)
	{
		attribute = at;
		value = v;
		permanent = perm;
		time = tim;
		to_delete = false;
	}
	~Buff()
	{

	}

	PLAYER_ATTRIBUTE attribute;
	int value;
	float time;
	bool permanent;
	bool to_delete;

	j1Timer buff_timer;

};

#endif _BUFF_H_