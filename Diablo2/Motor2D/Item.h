#ifndef _ITEM_H_
#define _ITEM_H_

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "Buff.h"

#include <vector>

#define ITEM_SLOT_SIZE 29



enum ITEM_TYPE
{
	ITEM_CONSUMABLE,
	ITEM_RING,
	ITEM_JEWEL,
	ITEM_STONE,
	ITEM_RUNE,
	ITEM_ARMOR,
	ITEM_GENERAL,
};

enum ITEM_RARITY
{
	RARITY_COMMON,
	RARITY_RARE,
	RARITY_LEGENDARY,
	NO_DROP,
};

enum PLAYER_ATTRIBUTE;
class GuiItem;
class EntItem;
struct buff;

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

	//Buff
	vector<Buff> item_buffs;

	//Both representations
	GuiItem* gui_item;
	EntItem* ent_item;
};

class itmConsumable : public Item
{
public:
	itmConsumable(ITEM_RARITY rarity, iPoint p);
public:
};

class itmRing : public Item
{
public:
	itmRing(ITEM_RARITY rarity, iPoint p);
public:
	//NOTE: 2 effects
};

class itmJewel : public Item
{
public:
	itmJewel(ITEM_RARITY rarity, iPoint p);
public:

	//NOTE: Also an effect
};

class itmStone : public Item
{
public:
	itmStone(ITEM_RARITY rare, iPoint p);

public:
	//Buff buff;
};

class itmRune : public Item
{
public:
	itmRune(ITEM_RARITY rarity, iPoint p);
public:
};

class itmArmor : public Item
{
public:
	itmArmor(ITEM_RARITY rarity, iPoint p);
public:
	
};
#endif _ITEM_H_