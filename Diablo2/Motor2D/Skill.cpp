#include "Skill.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Player.h"

Skill::Skill(SKILL_TYPE t) : skill_type(t), player(App->game->player)
{}


bool Skill::UnlockSkill()
{
	final_price = price + price_dt * (level + 1);

	if (player->blood_current >= (final_price) && (level + 1)<max_level)
	{
		player->blood_current -= final_price;
		player->PlayerEvent(BLOOD_DOWN);

		if (!unlocked)
		{
			unlocked = true;

			if (skill_type == SKILL_PASSIVE)
			{
				SkillInit();
			}
		}

		level++;
		CalculateSkillStats();

		return true;
	}
	return false;
}

bool Skill::UpdateCooldown()
{
	if (cooldown_timer.ReadSec() >= cooldown)
	{
		avaliable = true;
	}
	else
	{
		avaliable = false;
	}

	return true;
}