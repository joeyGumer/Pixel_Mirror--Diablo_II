#ifndef _GUI_MINIMAP_H_
#define _GUI_MINIMAP_H_

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include "GuiElements.h"
;
#include "Entity.h"
;
#include <vector>
#include <map>
#include <list>

;
using namespace std;

//class Skill;
class j1Player;


class GuiMiniMap : public GuiElement
{
public:
	GuiMiniMap(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list, SDL_Texture* texMapa);
	~GuiMiniMap();

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);


	//Called when there's a gui event
	void OnEvent(GuiElement* element, GUI_Event even);
	//Initializes all remaining data
	bool SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture);

public:

//	vector<Skill*>	skill_parents;
	//Skill*			skill;
	//GuiImage		image;
	//int				price;

public:
	SDL_Rect	rect;
	SDL_Rect	area;
	fPoint		scale;
	j1Player*	player;


	map<uint, Entity*>*   active_entities = NULL;
	SDL_Texture*		  tex = NULL;

	void		calculateScale();
	iPoint		minimapToWorld(const iPoint &mini_map_pos) const;
	iPoint		worldToMinimap(const iPoint &world_pos) const;
}



#endif _GUI_MINIMAP_H_

