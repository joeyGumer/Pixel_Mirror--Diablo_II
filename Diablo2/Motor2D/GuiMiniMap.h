#ifndef _GUI_MINIMAP_H_
#define _GUI_MINIMAP_H_

#include "SDL/include/SDL.h"
#include "GuiElements.h"
#include "j1Module.h"
#include "p2Point.h"
#include <vector>
;
using namespace std;

//class Skill;

class GuiMiniMap : public GuiElement
{
public:
	GuiMiniMap(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list);
	~GuiMiniMap();

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);

public:

//	vector<Skill*>	skill_parents;
	//Skill*			skill;
	GuiImage		image;
	int				price;

}



#endif _GUI_MINIMAP_H_

