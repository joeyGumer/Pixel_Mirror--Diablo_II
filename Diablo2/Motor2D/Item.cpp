#include "Item.h"
#include "EntItem.h"
#include "GuiItem.h"
#include "p2Defs.h"
#include "j1EntityManager.h"
#include "GuiInventory.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1HUD.h"
#include "hudInventory.h"
#include "j1Player.h"

Item::Item(ITEM_TYPE ty, ITEM_RARITY rare, iPoint p)
{
	type = ty;
	rarity = rare;

	//NOTE: temporal, testing with potion

	ent_item = NULL;
	gui_item = NULL;
}

Item::~Item()
{
	//NOTE: we'll, we'll need to change this, a fountain for memory leaks for sure
	RELEASE(coord);

	if (ent_item)
		RELEASE(ent_item);

	if (gui_item)
		RELEASE(gui_item);
}

//In charge to create the item, so it can be accesed from outside
void Item::CreateEntItem(iPoint &p)
{
	//NOTE: has to insert it to the entity manager! D:
	//ent_item = new EntItem(p, ID, rect);
	ent_item = ((EntItem*)App->game->em->Add(p, ITEM));
	ent_item->SetSprite(rect);
	ent_item->nexus = this;
}


//Changes from a entItem to guiItem and viceversa
void Item::ConvertToEntity(iPoint point)
{
	if (gui_item)
	{
		CreateEntItem(point);

		gui_item->inventory->items.remove(gui_item);
		RELEASE(gui_item);
	}
}

void Item::ConvertToGui()
{
	//NOTE: Change this to be accept a HUD_Element
	if (ent_item)
	{
		gui_item = new GuiItem(size, coord, rect);
		gui_item->nexus = this;
		if (App->game->HUD->inventory->AddItem(gui_item))
		{
			gui_item = NULL;
			App->game->em->Remove(ent_item->id);
			RELEASE(ent_item);
		}
	}
}

//The effect or buff that the item aplicates
void Item::Effect()
{

}


/*
//-------- Stones
*/

itmStone::itmStone(ITEM_RARITY rare, iPoint p) : Item(ITEM_STONE, rare, p)
{
	int x, y, value;
	PLAYER_ATTRIBUTE attribute;

	switch (rare)
	{
	case RARITY_COMMON:
		value = 4;
		value += rand() % 8;
		y = 947;
		break;
	case RARITY_RARE:
		value = 10;
		value += rand() % 10;
		y = 977;
		break;
	case RARITY_LEGENDARY:
		value = 17;
		value += rand() % 10;
		y = 1007;
		break;
	}

	int at = rand() % 5;

	switch (at)
	{
	case STRENGHT:
		attribute = STRENGHT;
		x = 2434;
		break;
	case DEXTERITY:
		attribute = DEXTERITY;
		x = 2404;
		break;
	case INTELLIGENCE:
		attribute = INTELLIGENCE;
		x = 2374;
		break;
	case VITALITY:
		attribute = VITALITY;
		x = 2344;
		break;
	case LUCK:
		attribute = LUCK;
		x = 2314;
		break;
	}

	buff = Buff(attribute, value);

	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}

	CreateEntItem(p);
}

/*
//---------Consumables
*/

itmConsumable::itmConsumable(ITEM_RARITY rarity, iPoint p) : Item(ITEM_CONSUMABLE, rarity, p)
{
	//NOTE: Have to apply %
	int at = rand() % 2;

	int x = 2464;
	int y;

	switch (at)
	{
	case 0:
		attribute = HP;
		switch (rarity)
		{
		case RARITY_COMMON:
			buff = 5; //%
			y = 797;
			break;
		case RARITY_RARE:
			buff = 7.5;
			y = 827;
			break;
		case RARITY_LEGENDARY:
			buff = 10;
			y = 857;
			break;
		}
		break;
	case 1:
		at = rand() % 5;
		buff = 15; //%

		switch (at)
		{
		case 0:
			attribute = BLOOD;
			y = 887;
			break;
		case 1:
			attribute = INTELLIGENCE;
			y = 917;
			break;
		case 2:
			attribute = DEXTERITY;
			y = 947;
			break;
		case 3:
			attribute = STRENGHT;
			y = 977;
			break;
		case 4:
			attribute = VITALITY;
			y = 1007;
			break;
		}
		
	}


	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}

	CreateEntItem(p);
}



/*
//---------Ring
*/

itmRing::itmRing(ITEM_RARITY rarity, iPoint p) : Item(ITEM_RING, rarity, p)
{
	int x;
	int y = 887;
	int at;

	switch (rarity)
	{
	case RARITY_COMMON:
		at = rand() % 2;

		switch (at)
		{
		case 0:
			x = 2374;
			break;
		case 1:
			x = 2404;
			break;
		}

		break;

	case RARITY_RARE:
		at = rand() % 2;

		switch (at)
		{
		case 0:
			x = 2344;
			break;
		case 1:
			x = 2434;
			break;
		}
		break;

	case RARITY_LEGENDARY:
		x = 2314;
		break;
	}


	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}

	CreateEntItem(p);
}

/*
//---------Jewel
*/

itmJewel::itmJewel(ITEM_RARITY rarity, iPoint p) : Item(ITEM_JEWEL, rarity, p)
{
	int x;
	int y = 917;

	switch (rarity)
	{
	case RARITY_COMMON:
		x = 2374;
		break;
	case RARITY_RARE:
		x = 2404;
		break;
	case RARITY_LEGENDARY:
		x = 2434;
		break;
	}

	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}

	CreateEntItem(p);
}


/*
//----------Rune
*/
itmRune::itmRune(ITEM_RARITY rarity, iPoint p) : Item(ITEM_RUNE, rarity, p)
{
	int y = 799;
	int x;

	switch (rarity)
	{
	case RARITY_COMMON:
		x = 2374;
		break;
	case RARITY_RARE:
		x = 2404;
		break;
	case RARITY_LEGENDARY:
		x = 2434;
		break;
	}

	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE * 3 };

	size = 3;
	coord = new iPoint[size];
	iPoint tmp[3] = { { 0, 0 }, { 0, 1 }, { 0, 2 } };

	for (int i = 0; i < size; i++)
	{
		coord[i] = tmp[i];
	}

	CreateEntItem(p);
}

/*
//----------Armor
*/

itmArmor::itmArmor(ITEM_RARITY rarity, iPoint p) : Item(ITEM_ARMOR, rarity, p)
{
	int y = 799;
	int x;

	switch (rarity)
	{
	case RARITY_COMMON:
		x = 2315;
		break;
	case RARITY_RARE:
		x = 2256;
		break;
	case RARITY_LEGENDARY:
		x = 2197;
		break;
	}

	rect = { x, y, ITEM_SLOT_SIZE * 2, ITEM_SLOT_SIZE * 3 };

	size = 6;
	coord = new iPoint[size];
	iPoint tmp[6] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } };

	for (int i = 0; i < size; i++)
	{
		coord[i] = tmp[i];
	}

	CreateEntItem(p);
}

