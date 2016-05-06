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
	Item(ITEM_TYPE, ITEM_RARITY);
	~Item();

public:
	//NOTE: here will be more things, like the name or description text

	//Kinds
	ITEM_RARITY rarity;
	ITEM_TYPE type;

	//Atributes for the GuiItem
	int size;
	iPoint* coord;
	SDL_Rect rect;

	//Both representations
	GuiItem* gui_item;
	EntItem* ent_item;
};

#endif _ITEM_H_