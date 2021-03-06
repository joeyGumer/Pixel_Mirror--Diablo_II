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
#include "j1SceneManager.h"
#include "j1Scene.h"

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

	if (!buff_given)
	{
		for (int i = 0; i < item_buffs.size(); i++)
		{
			RELEASE(item_buffs[i]);
		}
	}

	/*if (ent_item)
		RELEASE(ent_item);

	if (gui_item)
		RELEASE(gui_item);*/


}

void Item::DeleteBuffs()
{
	for (int i = 0; i < item_buffs.size(); i++)
	{
		RELEASE(item_buffs[i]);
	}

	item_buffs.clear();
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
		App->sm->current_scene->entity_list.push_back(ent_item);
	}

}


//Changes from a entItem to guiItem and viceversa
void Item::ConvertToEntity(iPoint point)
{
	if (gui_item)
	{
		CreateEntItem(point);

		gui_item->inventory->items.remove(gui_item);
		gui_item->convert = true;
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
		gui_item->CreateText();
		if (App->game->HUD->inventory->AddItem(gui_item))
		{
			ent_item->convert = true;

			App->game->em->Remove(ent_item->id);

			RELEASE(ent_item);
		}
		else
		{
			gui_item = NULL;
		}
	}
}

void Item::ConvertToGuiInv(GuiInventory* inv)
{
	if (ent_item)
	{
		gui_item = new GuiItem(size, coord, rect);
		gui_item->nexus = this;
		gui_item->CreateText();
		if (App->game->HUD->inventory->AddItem(gui_item, inv))
		{
			ent_item->convert = true;

			App->game->em->Remove(ent_item->id);

			RELEASE(ent_item);
		}
		else
		{
			gui_item = NULL;
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
	name = "GEM";
	switch (rare)
	{
	case RARITY_COMMON:
		value = 1;
		value += rand() % 7;
		y = 947;
		rarity_color = FONT_WHITE;
		break;
	case RARITY_RARE:
		value = 7;
		value += rand() % 7;
		y = 977;
		rarity_color = FONT_ORANGE;
		break;
	case RARITY_LEGENDARY:
		value = 13;
		value += rand() % 7;
		y = 1007;
		rarity_color = FONT_VIOLET; 
		
		break;
	}
	
	
	int at = rand() % 5;
	
	switch (at)
	{
	case STRENGHT:
		attribute =  STRENGHT;
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
	attribute_type.push_back(attribute);
	buff_value.push_back(value);
	Buff* buff; 
	buff = new Buff(attribute, value);
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
	name = "POTION";
	int x = 2464;
	int y;
	int value;
	PLAYER_ATTRIBUTE at;
	rarity_color = FONT_WHITE;
	switch (a)
	{
	case 0:
	{
		at = HP;
		switch (rarity)
		{
		case RARITY_COMMON:
			value = 20; //%
			y = 797;
			rarity_color = FONT_WHITE;
			break;
		case RARITY_RARE:
			value = 40;
			y = 827;
			rarity_color = FONT_ORANGE;
			break;
		case RARITY_LEGENDARY:
			value = 80;
			y = 857;
			rarity_color = FONT_VIOLET;
			break;
		}
	}
	break;

	case 1:
	{
		a = rand() % 5;
		value = 10; //%

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
	Buff* buff1;
	buff1 = new Buff(at, value, false, 15);
	item_buffs.push_back(buff1);

	attribute_type.push_back(at);
	buff_value.push_back(value);

	rect = { x, y, ITEM_SLOT_SIZE, ITEM_SLOT_SIZE };

	size = 1;
	coord = new iPoint[size];
	for (int i = 0; i < size; i++)
	{
		coord[i] = { 0, 0 };
	}
	
	CreateEntItem(p);
}

void itmConsumable::Effect()
{
	if (item_buffs[0]->attribute == HP)
	{
		App->game->player->RestoreHP(item_buffs[0]->value);
	}
	else if (item_buffs[0]->attribute == BLOOD)
	{
		App->game->player->MP_current += item_buffs[0]->value;
		App->game->player->PlayerEvent(MP_UP);
	}
	else
	{
		item_buffs[0]->value += (float(item_buffs[0]->value)/100) * App->game->player->extra_potion;

		App->game->player->buffs.push_back(item_buffs[0]);
		buff_given = true;
		item_buffs[0]->Start();
		App->game->player->PlayerEvent(CHANGE_ATTRIBUTE);
	}
}



/*
//---------Ring
*/

itmRing::itmRing(ITEM_RARITY rarity, iPoint p) : Item(ITEM_RING, rarity, p)
{
	int x;
	int y = 887;
	int at;
	name = "RING";
	switch (rarity)
	{
	case RARITY_COMMON:
	{
		at = rand() % 2;
		rarity_color = FONT_WHITE;
		switch (at)
		{
		case 0:
		{
			x = 2374;

			int r = 1;
			r += rand() % 5;
			Buff* buff1;
			buff1 = new Buff(PURE_BLOOD, r);
			item_buffs.push_back(buff1);
			attribute_type.push_back(PURE_BLOOD);
			buff_value.push_back(r);
			r = 1;
			r += rand() % 8;
			Buff* buff2;
			buff2 = new Buff(POTION, r);
			item_buffs.push_back(buff2);
			attribute_type.push_back(POTION);
			buff_value.push_back(r);
			
		}
		break;
		case 1:
		{
			x = 2404;

			int r = 1;
			r += rand() % 4;
			Buff* buff2;
			buff2 = new Buff(COOLDOWN, r);
			item_buffs.push_back(buff2);
			attribute_type.push_back(COOLDOWN);
			buff_value.push_back(r);
			r = 1;
			r += rand() % 10;
			Buff* buff1;
			buff1 = new Buff(BLOOD_MAX, r);
			item_buffs.push_back(buff1);
			attribute_type.push_back(BLOOD_MAX);
			buff_value.push_back(r);
		}
		break;
		}
	}
	break;

	case RARITY_RARE:
	{
		at = rand() % 2;
		rarity_color = FONT_ORANGE;
		switch (at)
		{
		case 0:
		{
			x = 2344;

			int r = 2;
			r += rand() % 9;
			Buff* buff1;
			buff1 = new Buff(PURE_BLOOD, r);
			item_buffs.push_back(buff1);
			attribute_type.push_back(PURE_BLOOD);
			buff_value.push_back(r);
			r = 10;
			r += rand() % 11;
			Buff* buff2;
			buff2 = new Buff(BLOOD_MAX, r);
			item_buffs.push_back(buff2);
			attribute_type.push_back(BLOOD_MAX);
			buff_value.push_back(r);
		}
			break;
		case 1:
		{
			x = 2434;

			int r = 1;
			r += rand() % 15;
			Buff* buff1;
			buff1 = new Buff(POTION, r);
			item_buffs.push_back(buff1);
			attribute_type.push_back(POTION);
			buff_value.push_back(r);
			r = 1;
			r += rand() % 4;
			Buff* buff2;
			buff2 = new Buff(ARMOR, r);
			item_buffs.push_back(buff2);
			attribute_type.push_back(ARMOR);
			buff_value.push_back(r);
		}
			break;
		}
	}
	break;

	case RARITY_LEGENDARY:
	{
		rarity_color = FONT_VIOLET;
		x = 2314;

		int r = 2;
		r += rand() % 5;
		Buff* buff1;
		buff1 = new Buff(ARMOR, r);
		item_buffs.push_back(buff1);
		attribute_type.push_back(ARMOR);
		buff_value.push_back(r);
		r = 2;
		r += rand() % 6;
		Buff* buff2;
		buff2 = new Buff(COOLDOWN, r);
		item_buffs.push_back(buff2);
		attribute_type.push_back(COOLDOWN);
		buff_value.push_back(r);
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
//---------Jewel
*/

itmJewel::itmJewel(ITEM_RARITY rarity, iPoint p) : Item(ITEM_JEWEL, rarity, p)
{
	int x;
	int y = 917;
	
	name = "JEWEL";
	
	switch (rarity)
	{
	case RARITY_COMMON:
	{
		x = 2374;
		rarity_color = FONT_WHITE;
		int value1 = 1 + (rand() % 5);
		int value2 = 1 + (rand() % 5);

		PLAYER_ATTRIBUTE attribute1 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);

		while (attribute2 == attribute1)
		{
			attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}

		Buff* buff1;
		buff1 = new Buff(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff* buff2;
		buff2 = new Buff(attribute2, value2);
		item_buffs.push_back(buff2);

		attribute_type.push_back(attribute1);
		buff_value.push_back(value1);

		attribute_type.push_back(attribute2);
		buff_value.push_back(value2);


		int special1 = 1 + (rand() % 7);
		Buff*buff3;
		buff3 = new Buff(COOLDOWN, special1);
		item_buffs.push_back(buff3);
	}
		break;
	case RARITY_RARE:
	{
		x = 2404;
		rarity_color = FONT_ORANGE;
		int value1 = 4 + (rand() % 6);
		int value2 = 4 + (rand() % 6);

		PLAYER_ATTRIBUTE attribute1 = (PLAYER_ATTRIBUTE)(rand() % 5);
		PLAYER_ATTRIBUTE attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);

		while (attribute2 == attribute1)
		{
			attribute2 = (PLAYER_ATTRIBUTE)(rand() % 5);
		}

		Buff* buff1;
		buff1 = new Buff(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff* buff2;
		buff2 = new Buff(attribute2, value2);
		item_buffs.push_back(buff2);

		int special1 = 1 + (rand() % 10);
		Buff* buff3;
		buff3 = new Buff(PURE_BLOOD, special1);
		item_buffs.push_back(buff3);

		attribute_type.push_back(attribute1);
		buff_value.push_back(value1);

		attribute_type.push_back(attribute2);
		buff_value.push_back(value2);
	}
		break;
	case RARITY_LEGENDARY:
	{
		x = 2434;
		rarity_color = FONT_VIOLET;
		int value1 = 7 + (rand() % 7);
		int value2 = 7 + (rand() % 7);
		int value3 = 7 + (rand() % 7);

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

		Buff* buff1;
		buff1 = new Buff(attribute1, value1);
		item_buffs.push_back(buff1);

		Buff* buff2;
		buff2 = new Buff(attribute2, value2);
		item_buffs.push_back(buff2);

		Buff* buff3;
		buff3 = new Buff(attribute3, value3);
		item_buffs.push_back(buff3);

		int special1 = 1 + (rand() % 5);
		Buff* buff4;
		buff4 = new Buff(ARMOR, special1);
		item_buffs.push_back(buff4);

		attribute_type.push_back(attribute1);
		buff_value.push_back(value1);

		attribute_type.push_back(attribute2);
		buff_value.push_back(value2);

		attribute_type.push_back(attribute3);
		buff_value.push_back(value3);

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
	name = "RUNE";
	
	switch (rarity)
	{
	case RARITY_COMMON:
	{
		x = 2374;
		rarity_color = FONT_WHITE;
		positive_buff = 5;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 7;
		negative_buff = -negative_buff;
	}
		break;
	case RARITY_RARE:
	{
		x = 2404;
		rarity_color = FONT_ORANGE;

		positive_buff = 10;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 13;
		negative_buff = -negative_buff;
	}
		break;
	case RARITY_LEGENDARY:
	{
		x = 2434;
		rarity_color = FONT_VIOLET;
		positive_buff = 15;
		positive_buff += rand() % 11;

		negative_buff = 1;
		negative_buff += rand() % 19;
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
	Buff* buff1;
	buff1 = new Buff(positive_attribute, positive_buff);
	item_buffs.push_back(buff1);

	Buff* buff2;
	buff2 = new Buff(negative_attribute, negative_buff);
	item_buffs.push_back(buff2);

	attribute_type.push_back(positive_attribute);
	buff_value.push_back(positive_buff);

	attribute_type.push_back(negative_attribute);
	buff_value.push_back(negative_buff);
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
	name = "ARMOR";
	switch (rarity)
	{
	case RARITY_COMMON:
		x = 2315;
		value = 1;
		rarity_color = FONT_WHITE;
		value += rand() % 10;
		break;
	case RARITY_RARE:
		x = 2256;
		value = 5;
		value += rand() % 11;
		rarity_color = FONT_ORANGE;
		break;
	case RARITY_LEGENDARY:
		x = 2197;
		value = 10;
		value += rand() % 11;
		rarity_color = FONT_VIOLET; 
		break;
	}

	Buff* buff;
	buff = new Buff(ARMOR, value);
	item_buffs.push_back(buff);
	
	rect = { x, y, ITEM_SLOT_SIZE * 2, ITEM_SLOT_SIZE * 3 };

	attribute_type.push_back(ARMOR);
	buff_value.push_back(value);

	size = 6;
	coord = new iPoint[size];
	iPoint tmp[6] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } };

	for (int i = 0; i < size; i++)
	{
		coord[i] = tmp[i];
	}

	CreateEntItem(p);
}

