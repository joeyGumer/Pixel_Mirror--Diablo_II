#ifndef _ITEM_H_
#define _ITEM_H_

#include "SDL/include/SDL.h"
#include "p2Point.h"

enum ITEM_TYPE
{
	ITEM_CONSUMABLE,
	ITEM_RING,
	ITEM_JEWEL,
	ITEM_STONE,
	ITEM_RUNE,
	ITEM_ARMOR,
};

enum ITEM_RARITY
{
	RARITY_COMMON,
	RARITY_RARE,
	RARITY_LEGENDARY,
};

class GuiItem;
class EntItem;

class Item
{
public:
	Item(ITEM_TYPE type , ITEM_RARITY rare, iPoint p);
	~Item();

	//In charge to create the item, so it can be accesed from outside
	void CreateEntItem(iPoint &p);

	//Changes from a entItem to guiItem and viceversa
	void ConvertToEntity(iPoint p);
	void ConvertToGui();

	//The effect or buff that the item aplicates
	//NOTE: may be changed to an structure, not a function, because when out, it should not do the effecct anymore
	virtual void Effect();

public:
	//NOTE: here will be more things, like the name or description text

	//Kinds
	ITEM_RARITY rarity;
	ITEM_TYPE type;

	//Atributes for the GuiItem
	int size;
	iPoint* coord;
	//NOTE: May be changed because now, we are using the same sprite for GuiItem and EntItem
	SDL_Rect rect;

	//Both representations
	GuiItem* gui_item;
	EntItem* ent_item;
};

#endif _ITEM_H_