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
	
	}
	~Buff()
	{

	}

	void Start()
	{
		if (!permanent)
		{
			buff_timer.Start();
		}
	}
	bool Update()
	{
		if (!permanent)
		{
			if (buff_timer.ReadSec() >= time)
			{
				return false;
			}
		}

		return true;
	}

	PLAYER_ATTRIBUTE attribute;
	int value;
	float time;
	bool permanent;


	j1Timer buff_timer;

};

#endif _BUFF_H_