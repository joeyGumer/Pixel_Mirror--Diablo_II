#include "hudInventory.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "GuiItem.h"
#include "GuiInventory.h"
#include "j1Player.h"
#include "Item.h"



//Constructor
//Don't now why the code makes me put semicolons everywhere
;
hudInventory::hudInventory() : hudElement()
{
	name.create("hud_inventory");
}

//Destructor
hudInventory::~hudInventory()
{

}

//Called before fist frame
bool hudInventory::Start()
{
	player = App->game->player;
	active = false;
	
	background = App->gui->AddGuiImage({ 321, 0 }, { 1128, 588, 319, 430 }, NULL, this);
	background->active = false;
	hud_gui_elements.push_back(background);
	
	closebutton = App->gui->AddGuiImage({ 12, 352 }, { 285, 192, 38, 38 }, background, this);
	closebutton->active = false;
	hud_gui_elements.push_back(closebutton);

	//Creation of the inventory
	inventory = App->gui->AddGuiInventory({ 16, 255 }, { 1144, 843, 290, 87 }, 10, 3, ITEM_SECTION_SIZE, ITEM_SECTION_SIZE, background, this);
	inventory->active = false;
	hud_gui_elements.push_back(inventory);

	//Armor
	armor = App->gui->AddGuiInventory({ 131, 31 }, { 1259, 619, 60, 89 }, 1, 1, 60, 89, background, this);
	armor->active = false;
	armor->slot_restriction = false;
	armor->restriction = ITEM_ARMOR;
	hud_gui_elements.push_back(armor);

	//Stones
	stone1 = App->gui->AddGuiInventory({ 45, 31 }, { 1173, 619, 29, 30 }, 1, 1, 29, 30, background, this);
	stone1->active = false;
	stone1->restriction = ITEM_STONE;
	hud_gui_elements.push_back(stone1);

	stone2 = App->gui->AddGuiInventory({ 45, 79 }, { 1173, 667, 29, 30 }, 1, 1, 29, 30, background, this);
	stone2->active = false;
	stone2->restriction = ITEM_STONE;
	hud_gui_elements.push_back(stone2);

	stone3 = App->gui->AddGuiInventory({ 45, 129 }, { 1173, 717, 29, 30 }, 1, 1, 29, 30, background, this);
	stone3->active = false;
	stone3->restriction = ITEM_STONE;
	hud_gui_elements.push_back(stone3);

	//Jewel
	jewel = App->gui->AddGuiInventory({ 248, 31 }, { 1376, 619, 29, 30 }, 1, 1, 29, 30, background, this);
	jewel->active = false;
	jewel->restriction = ITEM_JEWEL;
	hud_gui_elements.push_back(jewel);

	//Rings
	ring1 = App->gui->AddGuiInventory({ 248, 79 }, { 1376, 667, 29, 30 }, 1, 1, 29, 30, background, this);
	ring1->active = false;
	ring1->restriction = ITEM_RING;
	hud_gui_elements.push_back(ring1);

	ring2 = App->gui->AddGuiInventory({ 248, 129 }, { 1376, 717, 29, 30 }, 1, 1, 29, 30, background, this);
	ring2->active = false;
	ring2->restriction = ITEM_RING;
	hud_gui_elements.push_back(ring2);

	//Runes
	rune1 = App->gui->AddGuiInventory({ 93, 138 }, { 1221, 726, 31, 88 }, 1, 1, 31, 88, background, this);
	rune1->active = false;
	rune1->slot_restriction = false;
	rune1->restriction = ITEM_RUNE;
	hud_gui_elements.push_back(rune1);

	rune2 = App->gui->AddGuiInventory({ 145, 138 }, { 1273, 726, 31, 88 }, 1, 1, 31, 88, background, this);
	rune2->active = false;
	rune2->slot_restriction = false;
	rune2->restriction = ITEM_RUNE;
	hud_gui_elements.push_back(rune2);

	rune3 = App->gui->AddGuiInventory({ 197, 138 }, { 1325, 726, 31, 88 }, 1, 1, 31, 88, background, this);
	rune3->active = false;
	rune3->slot_restriction = false;
	rune3->restriction = ITEM_RUNE;
	hud_gui_elements.push_back(rune3);


	
	return true;
}

//Called before each loop iteration
bool hudInventory::PreUpdate()
{
	//Adding different item to the inventory
	/*if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		//Potion
		GuiItem* new_item;
		iPoint coords[1] = { { 0, 0 } };
		new_item = new GuiItem(1, coords, { 2285, 799, ITEM_SECTION_SIZE, ITEM_SECTION_SIZE });
		if (!inventory->AutomaticAddItem(new_item))
		{
			delete new_item;
		}
	
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		//Gauntlets
		GuiItem* new_item;
		int size = 4;
		iPoint coords[4] = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } };
		new_item = new GuiItem(4, coords, { 2286, 740, ITEM_SECTION_SIZE*2, ITEM_SECTION_SIZE*2 });
		if (!inventory->AutomaticAddItem(new_item))
		{
			delete new_item;
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		//Wand
		GuiItem* new_item;
		const int size = 2;
		iPoint coords[size] = { { 0, 0 }, { 0, 1 }};
		new_item = new GuiItem(size, coords, { 2315, 799, ITEM_SECTION_SIZE, ITEM_SECTION_SIZE * 2});
		if (!inventory->AutomaticAddItem(new_item))
		{
			delete new_item;
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		//Axe
		GuiItem* new_item;
		const int size = 6;
		iPoint coords[size] = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }, { 0, 2 }, { 1, 2} };
		new_item = new GuiItem(size, coords, { 2345, 740, ITEM_SECTION_SIZE * 2, ITEM_SECTION_SIZE * 3 });
		if (!inventory->AutomaticAddItem(new_item))
		{
			delete new_item;
		}

	}*/
	return true;
}

//Called each frame
bool hudInventory::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudInventory::PostUpdate()
{
	return true;
}

//Called before quitting
bool hudInventory::CleanUp()
{
	//WARNING: can't do this plox
	App->gui->dragged_item = NULL;
	if (inventory)
		inventory->CleanItems();

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == hud_gui_elements[i])
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	hud_gui_elements.clear();
	inventory = NULL;

	return true;
}

void hudInventory::Activate()
{
	active = !active;

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->active = active;
	}
}

bool hudInventory::AddItem(GuiItem* item, GuiInventory* inv)
{
	bool ret = true;
	//Potion

	if (!inv)
	{
		if (!inventory->AutomaticAddItem(item))
		{
			item->convert = true;
			RELEASE(item);
			ret = false;
		}

		return ret;
	}
	else
	{

		if (!inv->AutomaticAddItem(item))
		{
			item->convert = true;
			RELEASE(item);
			ret = false;
		}

		return ret;
	}


}

//Called when there's a gui event
void hudInventory::OnEvent(GuiElement* element, GUI_Event even)
{
	if (element->type == GUI_INVENTORY && element != inventory)
	{
		if (even == EVENT_ITEM_OUT)
		{
			//Danger using the remove here
			Item* it = (((GuiInventory*)element)->last_item_out->nexus);

			for (int i = 0; i < it->item_buffs.size(); i++)
			{
				player->buffs.remove((it->item_buffs[i]));
			}
			
			player->PlayerEvent(CHANGE_ATTRIBUTE);
		}
		else if (even == EVENT_ITEM_IN)
		{
			Item* it = (((GuiInventory*)element)->last_item_in->nexus);

			for (int i = 0; i < it->item_buffs.size(); i++)
			{
				player->buffs.push_back((it->item_buffs[i]));
			}
			player->PlayerEvent(CHANGE_ATTRIBUTE);
		}
	}
	else if (closebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			closebutton->SetTextureRect({ 324, 192, 38, 38 });
			closebutton_pressed = true;
		}
		break;
		}
	}
	
}

//Load/Save
bool hudInventory::Load(pugi::xml_node& node)
{
	//Main inventory
	pugi::xml_node invent = node.child("main_inventory");

	pugi::xml_node item = invent.child("gui_item");

	bool ret = false;

	for (; item; item = item.next_sibling("gui_item"))
	{
		LoadItemData(item, inventory);
	}

	//Armor
	invent = node.child("armor_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, armor);

	//Jewel
	invent = node.child("jewel_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, jewel);

	//Ring
	invent = node.child("ring1_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, ring1);

	invent = node.child("ring2_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, ring2);

	//Stone
	invent = node.child("stone1_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, stone1);

	invent = node.child("stone2_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, stone2);

	invent = node.child("stone3_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, stone3);

	//Rune
	invent = node.child("rune1_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, rune1);

	invent = node.child("rune2_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, rune2);

	invent = node.child("rune3_slot");
	item = invent.child("gui_item");
	if (item)
		LoadItemData(item, rune3);

	
	return true;
}

bool hudInventory::Save(pugi::xml_node& node) const
{
	//Main inventory
	pugi::xml_node invent = node.append_child("main_inventory");

	list<GuiItem*>::const_iterator gui_item = inventory->items.cbegin();

	for (; gui_item != inventory->items.cend(); gui_item++)
	{
		SaveItemData((*gui_item), invent);
	}

	//Armor
	pugi::xml_node invent_armor = node.append_child("armor_slot");
	gui_item = armor->items.cbegin();
	if (gui_item != armor->items.cend())
		SaveItemData((*gui_item), invent_armor);

	//Jewel
	pugi::xml_node invent_jewel = node.append_child("jewel_slot");
	gui_item = jewel->items.cbegin();
	if (gui_item != jewel->items.cend())
		SaveItemData((*gui_item), invent_jewel);

	//Ring
	pugi::xml_node invent_ring1 = node.append_child("ring1_slot");
	gui_item = ring1->items.cbegin();
	if (gui_item != ring1->items.cend())
		SaveItemData((*gui_item), invent_ring1);

	pugi::xml_node invent_ring2 = node.append_child("ring2_slot");
	gui_item = ring2->items.cbegin();
	if (gui_item != ring2->items.cend())
		SaveItemData((*gui_item), invent_ring2);

	//Stone
	pugi::xml_node invent_stone1 = node.append_child("stone1_slot");
	gui_item = stone1->items.cbegin();
	if (gui_item != stone1->items.cend())
		SaveItemData((*gui_item), invent_stone1);

	pugi::xml_node invent_stone2 = node.append_child("stone2_slot");
	gui_item = stone2->items.cbegin();
	if (gui_item != stone2->items.cend())
		SaveItemData((*gui_item), invent_stone2);

	pugi::xml_node invent_stone3 = node.append_child("stone3_slot");
	gui_item = stone3->items.cbegin();
	if (gui_item != stone3->items.cend())
		SaveItemData((*gui_item), invent_stone3);

	//Rune
	pugi::xml_node invent_rune1 = node.append_child("rune1_slot");
	gui_item = rune1->items.cbegin();
	if (gui_item != rune1->items.cend())
		SaveItemData((*gui_item), invent_rune1);

	pugi::xml_node invent_rune2 = node.append_child("rune2_slot");
	gui_item = rune2->items.cbegin();
	if (gui_item != rune2->items.cend())
		SaveItemData((*gui_item), invent_rune2);

	pugi::xml_node invent_rune3 = node.append_child("rune3_slot");
	gui_item = rune3->items.cbegin();
	if (gui_item != rune3->items.cend())
		SaveItemData((*gui_item), invent_rune3);

	return true;
}


void hudInventory::SaveItemData(GuiItem* gui_item, pugi::xml_node& invent)const
{
	Item* g_item = gui_item->nexus;

	pugi::xml_node item = invent.append_child("gui_item");

	item.append_attribute("rarity") = g_item->rarity;
	item.append_attribute("type") = g_item->type;

	pugi::xml_node rect = item.append_child("rect");

	rect.append_attribute("x") = g_item->rect.x;
	rect.append_attribute("y") = g_item->rect.y;
	rect.append_attribute("w") = g_item->rect.w;
	rect.append_attribute("h") = g_item->rect.h;

	for (int i = 0; i < g_item->item_buffs.size(); i++)
	{
		pugi::xml_node buff = item.append_child("buff");

		buff.append_attribute("type") = g_item->item_buffs[i]->attribute;
		buff.append_attribute("value") = g_item->item_buffs[i]->value;
	}
}


void hudInventory::LoadItemData(pugi::xml_node& item, GuiInventory* inv)
{
	Item* g_item = NULL;

	ITEM_TYPE tp = (ITEM_TYPE)item.attribute("type").as_int();
	ITEM_RARITY rarity = (ITEM_RARITY)item.attribute("rarity").as_int();

	iPoint pos = { int(App->game->player->p_position.x), int(App->game->player->p_position.y) };
	g_item = App->game->CreateItem(tp, rarity, pos);


	g_item->DeleteBuffs();

	for (pugi::xml_node bff = item.child("buff"); bff; bff = item.next_sibling("buff"))
	{
		Buff* buff;
		buff = new Buff((PLAYER_ATTRIBUTE)bff.attribute("type").as_int(), bff.attribute("value").as_int());
		g_item->item_buffs.push_back(buff);
	}

	g_item->rect.x = item.child("rect").attribute("x").as_int();
	g_item->rect.y = item.child("rect").attribute("y").as_int();
	g_item->rect.w = item.child("rect").attribute("w").as_int();
	g_item->rect.h = item.child("rect").attribute("h").as_int();

	g_item->ConvertToGuiInv(inv);
}