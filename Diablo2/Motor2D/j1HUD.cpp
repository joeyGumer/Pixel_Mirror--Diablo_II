#include "j1HUD.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1SceneManager.h"
#include "snIntro.h"
#include "hudElement.h"
#include "hudBelt.h"
#include "hudPause.h"
#include "hudInventory.h"
#include "hudBlood.h"
#include "hudSkilltree.h"
#include "hudStats.h"
#include "hudMiniMap.h"
#include "j1InputManager.h"

//NOTE : provisional
#include "j1Input.h"

//Constructor
j1HUD::j1HUD() : j1Module()
{	
	stats = new hudStats();
	belt = new hudBelt();
	pause_menu = new hudPause();
	inventory = new hudInventory();
	blood = new hudBlood();
	skilltree = new hudSkilltree();
	minimap = new hudMiniMap();


	HUD_elements.push_back(blood);
	HUD_elements.push_back(minimap);
	HUD_elements.push_back(stats);
	HUD_elements.push_back(inventory);
	HUD_elements.push_back(belt);
	HUD_elements.push_back(skilltree);
	HUD_elements.push_back(pause_menu);
	
	name.create("hud");
	
}

j1HUD::~j1HUD()
{
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		RELEASE(HUD_elements[i]);
	}

	HUD_elements.clear();
}

bool j1HUD::Start()
{
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		HUD_elements[i]->Start();
	}

	return true;
}

//Called before each loop iteration
bool j1HUD::PreUpdate()
{
	list<ShortCut*>::iterator it = App->im->shortcuts_list.begin();

	while (it != App->im->shortcuts_list.end())
	{
		if ((*it)->name == "Inventory" && (*it)->active)
		{
			if (skilltree->active == true)
			{
				inventory->Activate();
				skilltree->Activate();
				belt->inventorybutton_pressed = false;
			}
			else
			{
				inventory->Activate();
				belt->inventorybutton_pressed = false;
			}
		}

		if ((*it)->name == "Skill Tree" && (*it)->active)
		{ 
			if (inventory->active == true)
			{
				skilltree->Activate();
				inventory->Activate();
				belt->skilltreebutton_pressed = false;
			}
			else
			{
				skilltree->Activate();
				belt->skilltreebutton_pressed = false;
			}
		}

		if ((*it)->name == "Stats" && (*it)->active)
		{
			if (inventory->background->active == true && inventory->inventory->active == true)
			{
				stats->Activate();
				belt->statsbutton_pressed = false;
			}
			else
			{
				stats->Activate();
				belt->statsbutton_pressed = false;
			}
		}

		if ((*it)->name == "Map" && (*it)->active)
		{
			belt->minimapbutton_pressed = false;
			minimap->Activate();
		}

		++it;
	}

	if (belt->inventorybutton_pressed == true)
	{
		if (skilltree->active == true)
		{
			inventory->Activate();
			skilltree->Activate();
			belt->inventorybutton_pressed = false;
		}
		else
		{
			inventory->Activate();
			belt->inventorybutton_pressed = false;
		}
	}

	if (inventory->closebutton_pressed == true)
	{
		inventory->Activate();
		inventory->closebutton_pressed = false;
	}

	if (belt->skilltreebutton_pressed == true)
	{
		blood->hey_listen->active = false;
		blood->message_get = false;

		if (inventory->active == true)
		{
			skilltree->Activate();
			inventory->Activate();
			belt->skilltreebutton_pressed = false;
		}
		else
		{
			skilltree->Activate();
			belt->skilltreebutton_pressed = false;
		}
	}

	if (skilltree->martialdeletebutton_pressed == true)
	{
		skilltree->Activate();
		skilltree->martialdeletebutton_pressed = false;
	}

	if (belt->statsbutton_pressed == true)
	{
		if (inventory->background->active == true && inventory->inventory->active == true)
		{
			stats->Activate();
			belt->statsbutton_pressed = false;
		}
		else
		{
			stats->Activate();
			belt->statsbutton_pressed = false;
		}
	}

	if (stats->closebutton_pressed == true)
	{
		stats->Activate();
		stats->closebutton_pressed = false;
	}

	if ((App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) || belt->menubutton_pressed == true)
	{
		bool show_menu = true;

		if (stats->active == true)
		{
			stats->Activate();
			show_menu = false;
		}
		if (skilltree->active == true)
		{
			skilltree->Activate();
			show_menu = false;
		}
		if (inventory->active == true)
		{
			inventory->Activate();
			show_menu = false;
		}
		if (show_menu)
		{
			pause_menu->ActivateMenu();
		}

		belt->menubutton_pressed = false;
	}

	if (belt->minimapbutton_pressed == true)
	{
		belt->minimapbutton_pressed = false;
		minimap->Activate();
		
	}


	for (int i = 0; i < HUD_elements.size(); i++)
	{
		if (HUD_elements[i]->active)
			HUD_elements[i]->PreUpdate();
	}

	return true;
}

//Called each frame
bool j1HUD::Update(float dt)
{	
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		if (HUD_elements[i]->active)
			HUD_elements[i]->Update(dt);
	}


	return true;
}

//Called after each loop iteration
bool j1HUD::PostUpdate()
{
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		if (HUD_elements[i]->active)
			HUD_elements[i]->PostUpdate();
	}

	return true;
}

bool j1HUD::CleanUp()
{
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		HUD_elements[i]->CleanUp();
	}

	return true;
}

void j1HUD::OnEvent(GuiElement* element, GUI_Event even)
{

}



//Load/Save
bool j1HUD::Load(pugi::xml_node& node)
{
	for (int i = 0; i < HUD_elements.size(); i++)
	{
		pugi::xml_node item = node.child(HUD_elements[i]->name.GetString());
		HUD_elements[i]->Load(item);
	}

	return true;
}

bool j1HUD::Save(pugi::xml_node& node) const
{
	for(int i = 0; i < HUD_elements.size(); i++)
	{
		HUD_elements[i]->Save(node.append_child(HUD_elements[i]->name.GetString()));
	}

	return true;
}
