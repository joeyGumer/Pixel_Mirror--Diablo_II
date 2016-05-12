#include "GuiSkill.h"


;
GuiSkill::GuiSkill(iPoint p, SDL_Rect r, SDL_Rect r2, Skill* s, GuiElement* par, j1Module* list) : GuiElement(p, r, GUI_SKILL, par, list), image({ 0, 0 }, r, this, NULL), skill(s)
{
	interactable = true;

	locked = r;
	unlocked = r2;
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