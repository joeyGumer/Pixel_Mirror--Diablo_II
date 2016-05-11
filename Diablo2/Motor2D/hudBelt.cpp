#include "hudBelt.h"
#include "j1App.h"
#include "j1Gui.h"
//NOPE
#include "j1Game.h"
#include "j1HUD.h"
#include "j1Player.h"
#include "j1Input.h"

//NOTE: PROVISIONAL 
#include "j1Fonts.h"

#include "Item.h"

//Constructor
hudBelt::hudBelt():hudElement()
{
	active = true;
}

//Destructor
hudBelt::~hudBelt()
{}

//Called before fist frame
bool hudBelt::Start()
{
	//Player
	player = App->game->player;

	//
	life_current_h = mana_current_h = 78;

	HUD = App->gui->AddGuiImage({ 166, 430 }, { 166, 386, 408, 47 }, NULL, this);
	hud_gui_elements.push_back(HUD);

	inventory1 = App->gui->AddGuiInventory({ 176, 9 }, { 342, 395, 30, 30 }, 1, 1 , 30, 30, HUD, this);
	inventory1->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory1);
	inventory2 = App->gui->AddGuiInventory({ 207, 9 }, { 373, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory2->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory2);
	inventory3 = App->gui->AddGuiInventory({ 238, 9 }, { 404, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory3->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory3);
	inventory4 = App->gui->AddGuiInventory({ 269, 9 }, { 435, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory4->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory4);
	//HUD elements definition
	//NOTE: these position are very inaccurate

	HUDornament = App->gui->AddGuiImage({ 96, -5 }, { 262, 381, 115, 5 }, HUD, this);
	hud_gui_elements.push_back(HUDornament);

	HUDback1 = App->gui->AddGuiImage({ -132, -19 }, { 362, 226, 76, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback1);
	
	HUDback2 = App->gui->AddGuiImage({ 364, -18 }, { 437, 226, 80, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback2);

	life = App->gui->AddGuiImage({ -136, -44 }, { 371, 118, 79, 78 }, HUD, this);
	hud_gui_elements.push_back(life);

	mana = App->gui->AddGuiImage({ 365, -44 }, { 451, 118, 78, 78 }, HUD, this);
	hud_gui_elements.push_back(mana);

	stamina = App->gui->AddGuiImage({ 27, 20 }, { 530, 118, 102, 18 }, HUD, this);
	hud_gui_elements.push_back(stamina);

	life_holder = App->gui->AddGuiImage({ -166, -55 }, { 0, 331, 116, 103 }, HUD, this);
	hud_gui_elements.push_back(life_holder);

	mana_holder = App->gui->AddGuiImage({ 358, -55 }, { 524, 331, 116, 102 }, HUD, this);
	hud_gui_elements.push_back(mana_holder);

	runbutton = App->gui->AddGuiImage({ 9, 19 }, { 153, 280, 18, 22 }, HUD, this);
	runbutton->interactable = true;
	hud_gui_elements.push_back(runbutton);

	minipanelbutton = App->gui->AddGuiImage({ 146, 9 }, { 296, 253, 16, 27 }, HUD, this);
	minipanelbutton->interactable = true;
	hud_gui_elements.push_back(minipanelbutton);

	/*attack1 = App->gui->AddGuiImage({ -50, 0 }, { 102, 280, 50, 47 }, HUD, this);
	attack1->interactable = true;
	hud_gui_elements.push_back(attack1);

	attack2 = App->gui->AddGuiImage({ 308, 0 }, { 102, 280, 50, 47 }, HUD, this);
	attack2->interactable = true;
	hud_gui_elements.push_back(attack2);

	//Skills
	//Attack 1 ----------------------------------------
	skill11 = App->gui->AddGuiImage({ -51, -70 }, { 51, 280, 50, 47 }, HUD, this);
	skill11->interactable = true;
	skill11->active = false;
	hud_gui_elements.push_back(skill11);

	skill12 = App->gui->AddGuiImage({ 20, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill12->interactable = true;
	skill12->active = false;
	hud_gui_elements.push_back(skill12);

	skill13 = App->gui->AddGuiImage({ 91, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill13->interactable = true;
	skill13->active = false;
	hud_gui_elements.push_back(skill13);

	//Attack 2 ----------------------------------------
	skill21 = App->gui->AddGuiImage({ 305, -70 }, { 51, 280, 50, 47 }, HUD, this);
	skill21->interactable = true;
	skill21->active = false;
	hud_gui_elements.push_back(skill21);

	skill22 = App->gui->AddGuiImage({ 233, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill22->interactable = true;
	skill22->active = false;
	hud_gui_elements.push_back(skill22);

	skill23 = App->gui->AddGuiImage({ 162, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill23->interactable = true;
	skill23->active = false;
	hud_gui_elements.push_back(skill23);*/

	//Minipanel's buttons -------------------------------
	
	minipanel = App->gui->AddGuiImage({ 98, -25 }, { 170, 253, 110, 25 }, HUD, this);
	hud_gui_elements.push_back(minipanel);

	/*stats = App->gui->AddGuiImage({ 3, 3 }, { 170, 279, 20, 19 }, minipanel, this);
	stats->interactable = true;
	hud_gui_elements.push_back(stats);*/

	stats = App->gui->AddGuiImageWithLabel({ 3, 3 }, { 170, 279, 20, 19 }, "player", App->font->description, { -20, 0 }, minipanel, this);
	stats->interactable = true;
	hud_gui_elements.push_back(stats);

	inventorybutton = App->gui->AddGuiImageWithLabel({ 24, 3 }, { 191, 279, 20, 19 }, "invenTory", App->font->description, {-20, 0}, minipanel, this);
	inventorybutton->interactable = true;
	hud_gui_elements.push_back(inventorybutton);

	skilltree = App->gui->AddGuiImageWithLabel({ 45, 3 }, { 212, 279, 20, 19 }, "skill Tree", App->font->description, {-20, 0}, minipanel, this);
	skilltree->interactable = true;
	hud_gui_elements.push_back(skilltree);

	minimapbutton = App->gui->AddGuiImageWithLabel({ 66, 3 }, { 233, 279, 20, 19 }, "mini map", App->font->description, { 0, 0 }, minipanel, this);
	minimapbutton->interactable = true;
	hud_gui_elements.push_back(minimapbutton);

	game_menu = App->gui->AddGuiImageWithLabel({ 87, 3 }, { 254, 279, 20, 19 }, "game menu", App->font->description, {-20, 0}, minipanel, this);
	game_menu->interactable = true;
	hud_gui_elements.push_back(game_menu);
	


	minipanel->Desactivate();

	return true;
}

//Called before each loop iteration
bool hudBelt::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		RunningOn();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		list<GuiItem*>::iterator it = inventory1->items.begin();
		if (it != inventory1->items.end())
		{
			GuiItem* i = (*it);
			i->nexus->Effect();
			i->FreeSlots();
			inventory1->items.remove(i);
			RELEASE(i);
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		list<GuiItem*>::iterator it = inventory2->items.begin();
		if (it != inventory2->items.end())
		{
			GuiItem* i = (*it);
			i->nexus->Effect();
			i->FreeSlots();
			inventory2->items.remove(i);
			RELEASE(i);
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		list<GuiItem*>::iterator it = inventory3->items.begin();
		if (it != inventory3->items.end())
		{
			GuiItem* i = (*it);
			i->nexus->Effect();
			i->FreeSlots();
			inventory3->items.remove(i);
			RELEASE(i);
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		list<GuiItem*>::iterator it = inventory4->items.begin();
		if (it != inventory4->items.end())
		{
			GuiItem* i = (*it);
			i->nexus->Effect();
			i->FreeSlots();
			inventory4->items.remove(i);
			RELEASE(i);
		}

	}
	return true;
}

//Called each frame
bool hudBelt::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudBelt::PostUpdate()
{
	return true;
}

//Called before quitting
bool hudBelt::CleanUp()
{

	//NOTE: the problems between lists and vectors begin to grow, but i think this is a good way to approach this
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

	return true;
}

//Called when there's a gui event
void hudBelt::OnEvent(GuiElement* element, GUI_Event even)
{
	//HUD -------------------------------------
	//Run button
	if (runbutton == element)
	{
		switch (even)
		{
			case EVENT_MOUSE_LEFTCLICK_DOWN:
			{
				RunningOn();
			}
			break;
		}
	}

	//Mini panel button
	if (minipanelbutton == element)
	{
		switch (even)
		{
			case EVENT_MOUSE_LEFTCLICK_DOWN:
			{
				if (minipanel_pressed == false)
				{
					HUDornament->Desactivate();
					minipanel_pressed = true;
					minipanelbutton->SetTextureRect({ 281, 253, 16, 27 });
					minipanel->Activate();
				}
				else
				{
					HUDornament->Activate();
					minipanel_pressed = false;
					minipanelbutton->SetTextureRect({ 296, 253, 16, 27 });
					minipanel->Desactivate();
				}
			}
			break;
		}
	}
	
	//Inventory button
	if (inventorybutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (inventorybutton_pressed == false)
			{
				inventorybutton_pressed = true;
			}
			else
			{
				inventorybutton_pressed = false;
			}
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			inventorybutton->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			inventorybutton->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//Stats button
	if (stats == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (statsbutton_pressed == false)
			{
				 statsbutton_pressed = true;
			}
			else
			{
				statsbutton_pressed = false;
			}
		}
			break;
		case EVENT_MOUSE_ENTER:
		{
			stats->descriptionlabel->Activate();
		}
			break;
		case EVENT_MOUSE_EXIT:
		{
			stats->descriptionlabel->Desactivate();
		}
			break;
		}
	}

	//Skilltree button
	if (skilltree == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skilltreebutton_pressed == false)
				skilltreebutton_pressed = true;
			else
				skilltreebutton_pressed = false;
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			skilltree->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			skilltree->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//MiniMap button
	if (minimapbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (minimapbutton_pressed == false)
			{
				minimapbutton_pressed = true;
			}
			else
			{
				minimapbutton_pressed = false;
			}
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			minimapbutton->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			minimapbutton->descriptionlabel->Desactivate();
		}
		break;
		}
	}








	//Game_menu button
	if (game_menu == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (menubutton_pressed == false)
				menubutton_pressed = true;
			else
				menubutton_pressed = false;
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			game_menu->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			game_menu->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//Attack1
	/*if (attack1 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (attack1_pressed == false)
			{
				attack1_pressed = true;
				skill11->active = true;
				skill12->active = true;
				skill13->active = true;
			}
			else
			{
				attack1_pressed = false;
				skill11->active = false;
				skill12->active = false;
				skill13->active = false;
			}
		}
		break;
		}
	}

	//Attack2
	if (attack2 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (attack2_pressed == false)
			{
				attack2_pressed = true;
				skill21->active = true;
				skill22->active = true;
				skill23->active = true;
			}
			else
			{
				attack2_pressed = false;
				skill21->active = false;
				skill22->active = false;
				skill23->active = false;
			}
		}
		break;
		}
	}
	//Skills
	//Attack 1---------------------------------
	if (skill11 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill11->GetTextureRect();
			SDL_Rect rect2 = attack1->GetTextureRect();
			attack1->SetTextureRect(rect);
			skill11->SetTextureRect(rect2);
		}
		break;
		}
	}
	if (skill12 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill12->GetTextureRect();
			SDL_Rect rect2 = attack1->GetTextureRect();
			attack1->SetTextureRect(rect);
			skill12->SetTextureRect(rect2);
		}
		break;
		}
	}
	if (skill13 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill13->GetTextureRect();
			SDL_Rect rect2 = attack1->GetTextureRect();
			attack1->SetTextureRect(rect);
			skill13->SetTextureRect(rect2);
		}
		break;
		}
	}
	//Attack 2---------------------------------
	if (skill21 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill21->GetTextureRect();
			SDL_Rect rect2 = attack2->GetTextureRect();
			attack2->SetTextureRect(rect);
			skill21->SetTextureRect(rect2);
		}
		break;
		}
	}
	if (skill22 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill22->GetTextureRect();
			SDL_Rect rect2 = attack2->GetTextureRect();
			attack2->SetTextureRect(rect);
			skill22->SetTextureRect(rect2);
		}
		break;
		}
	}
	if (skill23 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			SDL_Rect rect = skill23->GetTextureRect();
			SDL_Rect rect2 = attack2->GetTextureRect();
			attack2->SetTextureRect(rect);
			skill23->SetTextureRect(rect2);
		}
		break;
		}
	}
	//HUD end ---------------------------------*/
}

//Sets the life stat at the HUD
void hudBelt::SetLife(int max_HP, int HP)
{
	if (HP != max_HP && HP != 0)
	{
		life_current_h = STAT_MAX_H / max_HP;
		life_current_h *= HP;
	}
	else if (max_HP == HP)
	{
		life_current_h = STAT_MAX_H;
	}
	else if (HP == 0)
	{
		life_current_h = 0;
	}

	/*if (App->debug)
	{
	life_debug->SetText(("%d / %d", HP, max_HP));
	}*/

	life->SetTextureRect({ 371, STAT_TEX_Y - int(life_current_h), 79, int(life_current_h) });
	life->SetLocalPosition({ -136, STAT_LOCAL_Y - int(life_current_h) });
}

//Sets the mana stat at the HUD
void hudBelt::SetMana(int max_MP, int MP)
{
	if (MP != max_MP && MP != 0)
	{
		mana_current_h = STAT_MAX_H / max_MP;
		mana_current_h *= MP;
	}
	else if (max_MP == MP)
	{
		mana_current_h = STAT_MAX_H;
	}
	else if (MP == 0)
	{
		mana_current_h = 0;
	}

	/*if (App->debug)
	{
	mana_debug->SetText("FUCK YOU");
	}*/

	mana->SetTextureRect({ 451, STAT_TEX_Y - int(mana_current_h), 78, int(mana_current_h) });
	mana->SetLocalPosition({ 366, STAT_LOCAL_Y - int(mana_current_h) });
}

void hudBelt::SetStamina(int max_ST, int ST)
{
	if (ST != max_ST && ST != 0)
	{
		stamina_current_w = STAT_MAX_W / max_ST;
		stamina_current_w *= ST;
	}
	else if (max_ST == ST)
	{
		stamina_current_w = STAT_MAX_W;
	}
	else if (ST == 0)
	{
		stamina_current_w = 0;
	}

	stamina->SetTextureRect({ 530, 118, int(stamina_current_w), 18 });
}

void hudBelt::RunningOn()
{
	bool run = player->RunOn();

	if (run)
	{
		runbutton->SetTextureRect({ 153, 301, 18, 22 });
	}
	else
	{
		runbutton->SetTextureRect({ 153, 280, 18, 22 });
	}
}