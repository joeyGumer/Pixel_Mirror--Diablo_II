#include "GuiSkill.h"

;
GuiSkill::GuiSkill(iPoint p, SDL_Rect r, Skill* s, GuiElement* par, j1Module* list) : GuiElement(p, r, GUI_SKILL, par, list), image({ 0, 0 }, r, this, NULL), skill(s)
{

}

GuiSkill::~GuiSkill()
{

}


void GuiSkill::Draw()
{
	image.Draw();
}

void GuiSkill::Update(GuiElement* hover, GuiElement* focus)
{

}