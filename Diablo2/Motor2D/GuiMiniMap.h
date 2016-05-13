#ifndef _GUI_MINIMAP_H_
#define _GUI_MINIMAP_H_

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include "GuiElements.h"
;
#include "Entity.h"
;
#include "EntEnemy.h"
;
#include <vector>
#include <map>
#include <list>

;
using namespace std;

class j1Player;
class SDL_Texture;
class Entity;

class GuiMiniMap : public GuiElement
{
public:
	GuiMiniMap(iPoint p, SDL_Rect r,SDL_Texture* tex, GuiElement* par, j1Module* list);
	~GuiMiniMap();

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);
	void SetAlpha(SDL_Texture* tex, Uint8 alpha);

public:
	
	fPoint		scale;
	iPoint		minimapToWorld(const iPoint &mini_map_pos);
	iPoint		WorldToMinimapi(const iPoint &world_pos);
	fPoint		WorldToMinimap(const fPoint &world_pos);
	void		DrawPlayer(j1Player* player);
	void		DrawEnemy(Entity* enemy);
	
	GuiImage image;
}



#endif _GUI_MINIMAP_H_

