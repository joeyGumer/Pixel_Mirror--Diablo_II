#include "Skill.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Player.h"

Skill::Skill(SKILL_TYPE t) : skill_type(t), player(App->game->player)
{}
