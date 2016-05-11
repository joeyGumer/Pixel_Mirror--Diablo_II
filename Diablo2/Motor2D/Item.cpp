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
	if (ent_item)
	{
		ent_item->SetSprite(rect);
		ent_item->nexus = this;
	}
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

	Buff buff(attribute, value);

	item_buffs.push_back(buff);

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
	int a = rand() % 2;

	int x = 2464;
	int y;
	int value;
	PLAYER_ATTRIBUTE at;

	switch (a)
	{
	case 0:
	{
		at = HP;
		switch (rarity)
		{
		case RARITY_COMMON:
			value = 5; //%
			y = 797;
			break;
		case RARITY_RARE:
			value = 7.5;
			y = 827;
			break;
		case RARITY_LEGENDARY:
			value = 10;
			y = 857;
			break;
		}
	}
	break;

	case 1:
	{
		a = rand() % 5;
		value = 15; //%

		switch (a)
		{
		case 0:
		{
			at = BLOOD;
			y = 887;
		}
		break;
		case 1:
		{
			at = INTELLIGENCE;
			y = 917;
		}
		break;
		case 2:
		{
			at = DEXTERITY;
			y = 947;
		}
		break;
		case 3:
		{
			at = STRENGHT;
			y = 977;
		}
		break;
		case 4:
		{
			at = VITALITY;
			y = 1007;
		}
		break;
		}

	}
	break;
	}

	Buff buff1(at, value);
	item_buffs.push_back(buff1);

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
	{
		x = 2374;
		
		int value1 = 1 + (rand() % 10);
		int value2 = 1 + (rand() % 10);

		PLAYER_ATTRIBUTE attribute1 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);

		while (attribute2 == attribute1)
		{
			attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}

		Buff buff1(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff buff2(attribute2, value2);
		item_buffs.push_back(buff2);

		int special1 = 4 + (rand() % 4);
		Buff buff3(COOLDOWN, special1);
		item_buffs.push_back(buff3);
	}
		break;
	case RARITY_RARE:
	{
		x = 2404;

		int value1 = 5 + (rand() % 11);
		int value2 = 5 + (rand() % 11);

		PLAYER_ATTRIBUTE attribute1 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);

		while (attribute2 == attribute1)
		{
			attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}

		Buff buff1(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff buff2(attribute2, value2);
		item_buffs.push_back(buff2);

		int special1 = 5 + (rand() % 11);
		Buff buff3(BLOOD, special1);
		item_buffs.push_back(buff3);

	}
		break;
	case RARITY_LEGENDARY:
	{
		x = 2434;

		int value1 = 5 + (rand() % 16);
		int value2 = 5 + (rand() % 16);
		int value3 = 5 + (rand() % 16);

		PLAYER_ATTRIBUTE attribute1 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute3 = (PLAYER_ATTRIBUTE)(rand() % 5);

		while (attribute2 == attribute1)
		{
			attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}
		while (attribute2 == attribute3 || attribute1 == attribute3)
		{
			attribute3 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}

		Buff buff1(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff buff2(attribute2, value2);
		item_buffs.push_back(buff2);

		Buff buff3(attribute3, value3);
		item_buffs.push_back(buff3);

		int special1 = 1 + (rand() % 8);
		Buff buff4(ARMOR, special1);
		item_buffs.push_back(buff4);
	}
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
	int positive_buff, negative_buff;
	PLAYER_ATTRIBUTE positive_attribute, negative_attribute;
	int r;

	switch (rarity)
	{
	case RARITY_COMMON:
	{
		x = 2374;

		positive_buff = 10;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 10;
		negative_buff = -negative_buff;
	}
		break;
	case RARITY_RARE:
	{
		x = 2404;


		positive_buff = 20;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 15;
		negative_buff = -negative_buff;
	}
		break;
	case RARITY_LEGENDARY:
	{
		x = 2434;

		positive_buff = 30;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 20;
		negative_buff = -negative_buff;
	}
		break;
	}

	positive_attribute = (PLAYER_ATTRIBUTE)(rand() % 5);
	negative_attribute = (PLAYER_ATTRIBUTE)(rand() % 5);

	while (positive_attribute == negative_attribute)
	{
		negative_attribute = (PLAYER_ATTRIBUTE)(rand() % 5);
	}

	//Buffs
	Buff buff1(positive_attribute, positive_buff);
	item_buffs.push_back(buff1);

	Buff buff2(negative_attribute, negative_buff);
	item_buffs.push_back(buff2);

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
	int value;

	switch (rarity)
	{
	case RARITY_COMMON:
		x = 2315;
		value = 7;
		value += rand() % 4;
		break;
	case RARITY_RARE:
		x = 2256;
		value = 10;
		value += rand() % 6;
		break;
	case RARITY_LEGENDARY:
		x = 2197;
		value = 17;
		value += rand() % 9;
		break;
	}

	Buff buff(ARMOR, value);
	item_buffs.push_back(buff);

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

