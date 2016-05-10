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

bool hudInventory::AddItem(GuiItem* item)
{
	bool ret = true;
	//Potion
	if (!inventory->AutomaticAddItem(item))
	{
		RELEASE(item);
		ret = false;
	}

	return ret;
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
				player->buffs.remove(&(it->item_buffs[i]));
			}
			
			player->PlayerEvent(CHANGE_ATTRIBUTE);
		}
		else if (even == EVENT_ITEM_IN)
		{
			Item* it = (((GuiInventory*)element)->last_item_in->nexus);

			for (int i = 0; i < it->item_buffs.size(); i++)
			{
				player->buffs.push_back(&(it->item_buffs[i]));
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
