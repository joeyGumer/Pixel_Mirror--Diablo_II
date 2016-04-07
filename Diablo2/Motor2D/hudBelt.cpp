#include "hudBelt.h"
#include "j1App.h"
#include "j1Gui.h"
//NOPE
#include "j1Game.h"
#include "j1HUD.h"



//Constructor
hudBelt::hudBelt():hudElement()
{}

//Destructor
hudBelt::~hudBelt()
{}

//Called before fist frame
bool hudBelt::Start()
{
	life_current_h = mana_current_h = 78;

	HUD = App->gui->AddGuiImage({ 166, 553 }, { 166, 386, 468, 47 }, NULL, this);
	hud_gui_elements.push_back(HUD);

	//HUD elements definition
	//NOTE: these position are very inaccurate

	HUDback1 = App->gui->AddGuiImage({ -132, -19 }, { 362, 226, 76, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback1);
	
	HUDback2 = App->gui->AddGuiImage({ 524, -19 }, { 437, 226, 80, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback2);

	life = App->gui->AddGuiImage({ -136, -45 }, { 371, 118, 79, 78 }, HUD, this);
	hud_gui_elements.push_back(life);

	mana = App->gui->AddGuiImage({ 524, -45 }, { 451, 118, 78, 78 }, HUD, this);
	hud_gui_elements.push_back(mana);

	stamina = App->gui->AddGuiImage({ 107, 20 }, { 530, 118, 102, 18 }, HUD, this);
	hud_gui_elements.push_back(stamina);

	life_holder = App->gui->AddGuiImage({ -166, -55 }, { 0, 331, 116, 103 }, HUD, this);
	hud_gui_elements.push_back(life_holder);

	mana_holder = App->gui->AddGuiImage({ 518, -55 }, { 684, 331, 116, 103 }, HUD, this);
	hud_gui_elements.push_back(mana_holder);

	runbutton = App->gui->AddGuiImage({ 89, 19 }, { 153, 280, 18, 22 }, HUD, this);
	runbutton->interactable = true;
	hud_gui_elements.push_back(runbutton);

	minipanelbutton = App->gui->AddGuiImage({ 225, 9 }, { 337, 252, 16, 27 }, HUD, this);
	minipanelbutton->interactable = true;
	hud_gui_elements.push_back(minipanelbutton);

	attack1 = App->gui->AddGuiImage({ -50, 0 }, { 102, 280, 50, 47 }, HUD, this);
	attack1->interactable = true;
	hud_gui_elements.push_back(attack1);

	attack2 = App->gui->AddGuiImage({ 468, 0 }, { 102, 280, 50, 47 }, HUD, this);
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
	skill21 = App->gui->AddGuiImage({ 467, -70 }, { 51, 280, 50, 47 }, HUD, this);
	skill21->interactable = true;
	skill21->active = false;
	hud_gui_elements.push_back(skill21);

	skill22 = App->gui->AddGuiImage({ 396, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill22->interactable = true;
	skill22->active = false;
	hud_gui_elements.push_back(skill22);

	skill23 = App->gui->AddGuiImage({ 325, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill23->interactable = true;
	skill23->active = false;
	hud_gui_elements.push_back(skill23);

	//Minipanel's buttons -------------------------------
	stats = App->gui->AddGuiImage({ -23, -33 }, { 170, 253, 24, 25 }, HUD, this);
	stats->interactable = true;
	minipanelbutton->AddChild(stats);
	hud_gui_elements.push_back(stats);

	skilltree = App->gui->AddGuiImage({ 0, -33 }, { 193, 253, 22, 25 }, HUD, this);
	skilltree->interactable = true;
	minipanelbutton->AddChild(skilltree);
	hud_gui_elements.push_back(skilltree);

	inventory = App->gui->AddGuiImage({ 21, -33 }, { 214, 253, 22, 25 }, HUD, this);
	inventory->interactable = true;
	minipanelbutton->AddChild(inventory);
	hud_gui_elements.push_back(inventory);

	map = App->gui->AddGuiImage({ 41, -33 }, { 235, 253, 22, 25 }, HUD, this);
	map->interactable = true;
	minipanelbutton->AddChild(map);
	hud_gui_elements.push_back(map);

	message_log = App->gui->AddGuiImage({ 63, -33 }, { 256, 253, 22, 25 }, HUD, this);
	message_log->interactable = true;
	minipanelbutton->AddChild(message_log);
	hud_gui_elements.push_back(message_log);

	search_log = App->gui->AddGuiImage({ 86, -33 }, { 277, 253, 22, 25 }, HUD, this);
	search_log->interactable = true;
	minipanelbutton->AddChild(search_log);
	hud_gui_elements.push_back(search_log);

	game_menu = App->gui->AddGuiImage({ 107, -33 }, { 298, 253, 24, 25 }, HUD, this);
	game_menu->interactable = true;
	minipanelbutton->AddChild(game_menu);
	hud_gui_elements.push_back(game_menu);
	minipanelbutton->DesactivateChilds();
	return true;
}

//Called before each loop iteration
bool hudBelt::PreUpdate()
{
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
				if (run_pressed == false)
				{
					run_pressed = true;
					runbutton->SetTextureRect({ 153, 301, 18, 22 });
				}
				else
				{
					run_pressed = false;
					 runbutton->SetTextureRect({ 153, 280, 18, 22 });
				}
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
					minipanel_pressed = true;
					minipanelbutton->SetTextureRect({ 322, 252, 16, 27 });
					minipanelbutton->ActivateChilds();
				}
				else
				{
					minipanel_pressed = false;
				    minipanelbutton->SetTextureRect({ 337, 252, 16, 27 });
					minipanelbutton->DesactivateChilds();
				}
			}
			break;
		}
	}
	//Attack1
	if (attack1 == element)
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
	//HUD end ---------------------------------
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
	mana->SetLocalPosition({ 524, STAT_LOCAL_Y - int(mana_current_h) });
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