#include "hudInventory.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "GuiItem.h"
#include "GuiInventory.h"



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
	active = false;
	
	background = App->gui->AddGuiImage({ 321, 0 }, { 1128, 588, 319, 430 }, NULL, this);
	background->active = false;
	hud_gui_elements.push_back(background);
	
	//Creation of the inventory
	inventory = App->gui->AddGuiInventory({ 16, 255 }, { 1144, 843, 290, 87 }, 10, 3, ITEM_SECTION_SIZE, ITEM_SECTION_SIZE, background, this);
	inventory->active = false;
	hud_gui_elements.push_back(inventory);
	
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
		delete item;
		ret = false;
	}

	return ret;
}

//Called when there's a gui event
void hudInventory::OnEvent(GuiElement* element, GUI_Event even)
{

}
