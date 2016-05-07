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
	int x, y;

	switch (rare)
	{
	case RARITY_COMMON:
		buff = 4;
		buff += rand() % 8;
		y = 947;
		break;
	case RARITY_RARE:
		buff = 10;
		buff += rand() % 10;
		y = 977;
		break;
	case RARITY_LEGENDARY:
		buff = 17;
		buff += rand() % 10;
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

	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}

	CreateEntItem(p);
}
