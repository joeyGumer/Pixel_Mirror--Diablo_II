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

	runbutton = App->gui->AddGuiImage({ 88, 19 }, { 148, 279, 18, 22 }, HUD, this);
	runbutton->interactable = true;
	hud_gui_elements.push_back(runbutton);

	minipanelbutton = App->gui->AddGuiImage({ 225, 9 }, { 337, 252, 16, 27 }, HUD, this);
	minipanelbutton->interactable = true;
	hud_gui_elements.push_back(minipanelbutton);

	attack1 = App->gui->AddGuiImage({ -51, 0 }, { 97, 280, 52, 47 }, HUD, this);
	attack1->interactable = true;
	hud_gui_elements.push_back(attack1);

	attack2 = App->gui->AddGuiImage({ 467, 0 }, { 97, 280, 52, 47 }, HUD, this);
	attack2->interactable = true;
	hud_gui_elements.push_back(attack2);

	//Minipanel's buttons
	stats = App->gui->AddGuiImage({ 157, -23 }, { 170, 253, 24, 25 }, HUD, this);
	stats->interactable = true;
	stats->active = false;
	hud_gui_elements.push_back(stats);

	skilltree = App->gui->AddGuiImage({ 180, -23 }, { 193, 253, 22, 25 }, HUD, this);
	skilltree->interactable = true;
	skilltree->active = false;
	hud_gui_elements.push_back(skilltree);

	inventory = App->gui->AddGuiImage({ 201, -23 }, { 214, 253, 22, 25 }, HUD, this);
	inventory->interactable = true;
	inventory->active = false;
	hud_gui_elements.push_back(inventory);

	map = App->gui->AddGuiImage({ 222, -23 }, { 235, 253, 22, 25 }, HUD, this);
	map->interactable = true;
	map->active = false;
	hud_gui_elements.push_back(map);

	message_log = App->gui->AddGuiImage({ 243, -23 }, { 256, 253, 22, 25 }, HUD, this);
	message_log->interactable = true;
	message_log->active = false;
	hud_gui_elements.push_back(message_log);

	search_log = App->gui->AddGuiImage({ 264, -23 }, { 277, 253, 22, 25 }, HUD, this);
	search_log->interactable = true;
	search_log->active = false;
	hud_gui_elements.push_back(search_log);

	game_menu = App->gui->AddGuiImage({ 285, -23 }, { 298, 253, 24, 25 }, HUD, this);
	game_menu->interactable = true;
	game_menu->active = false;
	hud_gui_elements.push_back(game_menu);

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
					runbutton->SetTextureRect({ 148, 300, 18, 22 });
				}
				else
				{
					run_pressed = false;
					 runbutton->SetTextureRect({ 148, 279, 18, 22 });
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
					stats->active = true;
					skilltree->active = true;
					inventory->active = true;
					map->active = true;
				    message_log->active = true;
				    search_log->active = true;
				    game_menu->active = true;
				}
				else
				{
					minipanel_pressed = false;
				    minipanelbutton->SetTextureRect({ 337, 252, 16, 27 });
					stats->active = false;
					skilltree->active = false;
					inventory->active = false;
					map->active = false;
					message_log->active = false;
					search_log->active = false;
					game_menu->active = false;
				}
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