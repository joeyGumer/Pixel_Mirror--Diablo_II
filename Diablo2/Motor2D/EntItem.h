#ifndef __ENT_ITEM_H__
#define __ENT_ITEM_H__

#include "EntStatic.h"

class j1Player;
class Item;
class EntItem : public EntStatic
{
public:
	EntItem(const iPoint &p, uint ID);

	void Draw()
	{}
	void DrawDebug()
	{}

	void SetSprite(SDL_Rect r);

public:
	
	Item* nexus = NULL;
};



/*class itmPotionHP : public EntItem
{
public:
	itmPotionHP(const iPoint &p, uint ID);

	void Effect();
	
	int HP_points = 50;
};*/
#endif