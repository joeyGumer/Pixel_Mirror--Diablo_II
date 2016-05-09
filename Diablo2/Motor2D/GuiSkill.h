#ifndef _GUI_SKILL_H_
#define _GUI_SKILL_H_

#include "SDL/include/SDL.h"
#include "GuiElements.h"
#include "j1Module.h"
#include "p2Point.h"
#include <vector>

using namespace std;

class Skill;

class GuiSkill : public GuiElement
{
public:
	GuiSkill(iPoint p, SDL_Rect r, Skill* s, GuiElement* par, j1Module* list);
	~GuiSkill();

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);

public:

	vector<Skill*>	skill_parents;
	Skill*			skill;
	GuiImage		image;
	int				price;

}



#endif _GUI_SKILLL_H_