#include "Item.h"
#include "EntItem.h"
#include "GuiItem.h"
#include "p2Defs.h"
#include "j1EntityManager.h"
#include "GuiInventory.h"
#include "j1App.h"
#include "j1Game.h"

Item::Item(ITEM_TYPE ty, ITEM_RARITY rare)
{
	type = ty;
	rarity = rare;

	//NOTE: temporal, testing with potion
	size = 1;
	coord = new iPoint[size];
	rect = { 2285, 799, 29, 29 };

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
void Item::CreateEntItem(const iPoint &p, uint ID)
{
	//NOTE: has to insert it to the entity manager! D:
	ent_item = new EntItem(p, ID, rect);
}


//Changes from a entItem to guiItem and viceversa
void Item::ConvertItem(uint ID, iPoint point)
{
	if (ent_item)
	{
		gui_item = new GuiItem(size, coord, rect);
		
		App->game->em->Remove(ent_item->id);
		RELEASE(ent_item);
	}
	else if (gui_item)
	{
		CreateEntItem(point, ID);

		//NOTE: in process

	}
}

//The effect or buff that the item aplicates
void Item::Effect()
{

}