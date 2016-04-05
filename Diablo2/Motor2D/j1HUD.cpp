#include "j1HUD.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1SceneManager.h"
#include "snIntro.h"

//NOTE : provisional
#include "j1Input.h"

//Constructor
j1HUD::j1HUD() : j1Module()
{

}

j1HUD::~j1HUD()
{}

bool j1HUD::Start()
{
	//NOTE: totally have to change this system...
		main_menu = false;


		life_current_h = mana_current_h = 78;
		stamina_current_w = 102;

		HUD = App->gui->AddGuiImage({ 166, 553 }, { 166, 386, 468, 47 }, NULL, this);
		HUD_elements.push_back(HUD);

		//HUD elements definition
		//NOTE: these position are very inaccurate

		HUDback1 = App->gui->AddGuiImage({ -132, -19 }, { 362, 226, 76, 53 }, HUD, this);
		HUD_elements.push_back(HUDback1);

		HUDback2 = App->gui->AddGuiImage({ 524, -19 }, { 437, 226, 80, 53 }, HUD, this);
		HUD_elements.push_back(HUDback2);

		life = App->gui->AddGuiImage({ -136, -45 }, { 371, 118, 79, 78 }, HUD, this);
		HUD_elements.push_back(life);

		mana = App->gui->AddGuiImage({ 524, -45 }, { 451, 118, 78, 78 }, HUD, this);
		HUD_elements.push_back(mana);

		stamina = App->gui->AddGuiImage({ 107, 20 }, { 530, 118, 102, 18 }, HUD, this);
		HUD_elements.push_back(stamina);

		life_holder = App->gui->AddGuiImage({ -166, -55 }, { 0, 331, 116, 103 }, HUD, this);
		HUD_elements.push_back(life_holder);

		mana_holder = App->gui->AddGuiImage({ 518, -55 }, { 684, 331, 116, 103 }, HUD, this);
		HUD_elements.push_back(mana_holder);

		runbutton = App->gui->AddGuiImage({ 88, 19 }, { 148, 279, 18, 22 }, HUD, this);
		runbutton->interactable = true;
		HUD_elements.push_back(runbutton);

		minipanelbutton = App->gui->AddGuiImage({ 225, 9 }, { 337, 252, 16, 27 }, HUD, this);
		minipanelbutton->interactable = true;
		HUD_elements.push_back(minipanelbutton);

		attack1 = App->gui->AddGuiImage({ -51, 0 }, { 97, 280, 52, 47 }, HUD, this);
		attack1->interactable = true;
		HUD_elements.push_back(attack1);

		attack2 = App->gui->AddGuiImage({ 467, 0 }, { 97, 280, 52, 47 }, HUD, this);
		attack2->interactable = true;
		HUD_elements.push_back(attack2);

		//Minipanel's buttons
		stats = App->gui->AddGuiImage({ 157, -23 }, { 170, 253, 24, 25 }, HUD, this);
		stats->interactable = true;
		stats->active = false;
		HUD_elements.push_back(stats);

		skilltree = App->gui->AddGuiImage({ 180, -23 }, { 193, 253, 22, 25 }, HUD, this);
		skilltree->interactable = true;
		skilltree->active = false;
		HUD_elements.push_back(skilltree);

		inventory = App->gui->AddGuiImage({ 201, -23 }, { 214, 253, 22, 25 }, HUD, this);
		inventory->interactable = true;
		inventory->active = false;
		HUD_elements.push_back(inventory);

		map = App->gui->AddGuiImage({ 222, -23 }, { 235, 253, 22, 25 }, HUD, this);
		map->interactable = true;
		map->active = false;
		HUD_elements.push_back(map);

		message_log = App->gui->AddGuiImage({ 243, -23 }, { 256, 253, 22, 25 }, HUD, this);
		message_log->interactable = true;
		message_log->active = false;
		HUD_elements.push_back(message_log);

		search_log = App->gui->AddGuiImage({ 264, -23 }, { 277, 253, 22, 25 }, HUD, this);
		search_log->interactable = true;
		search_log->active = false;
		HUD_elements.push_back(search_log);

		game_menu = App->gui->AddGuiImage({ 285, -23 }, { 298, 253, 24, 25 }, HUD, this);
		game_menu->interactable = true;
		game_menu->active = false;
		HUD_elements.push_back(game_menu);

		//Menu
		options = App->gui->AddGuiImage({ 310, 130 }, { 395, 71, 194, 31 }, NULL, this);
		options->interactable = true;
		options->active = false;
		HUD_elements.push_back(options);

		saveandexit = App->gui->AddGuiImage({ 145, 200 }, { 460, 0, 534, 35 }, NULL, this);
		saveandexit->interactable = true;
		saveandexit->active = false;
		HUD_elements.push_back(saveandexit);

		returntogame = App->gui->AddGuiImage({ 195, 270 }, { 994, 0, 438, 35 }, NULL, this);
		returntogame->interactable = true;
		returntogame->active = false;
		HUD_elements.push_back(returntogame);

		//Debug labels
		//NOTE : coming soon
		/*life_debug = App->gui->AddGuiLabel("", NULL, { 0, 0 }, life, this);
		life_debug->Center(true, true);
		life_debug->debug = true;

		mana_debug = App->gui->AddGuiLabel("", NULL, { 0, 0 }, mana, this);
		mana_debug->Center(true, true);
		mana_debug->debug = true;*/

	return true;
}

//Called before each loop iteration
bool j1HUD::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ActivateMenu();
	}


	if (main_menu == true)
	{
		ActivateMenu();
		App->sm->ChangeScene(App->sm->intro);
	}

	return true;
}

//Called each frame
bool j1HUD::Update(float dt)
{	
	return true;
}

//Called after each loop iteration
bool j1HUD::PostUpdate()
{
	return true;
}

bool j1HUD::CleanUp()
{
	for (list<GuiElement*>::iterator item = HUD_elements.begin(); item != HUD_elements.end(); item++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == (*item))
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	HUD_elements.clear();

	return true;
}

void j1HUD::OnEvent(GuiElement* element, GUI_Event even)
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

	//Game menu --------------------------------
	//SaveAndExit button -----------------------------------------------------------------------------
	if (saveandexit == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			main_menu = true;
			break;
		}
	}

	//ReturnToGame button -----------------------------------------------------------------------------
	if (returntogame == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			ActivateMenu();
			break;
		}
	}
}

//Sets the life stat at the HUD
void j1HUD::SetLife(int max_HP, int HP)
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
void j1HUD::SetMana(int max_MP, int MP)
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

void j1HUD::SetStamina(int max_ST, int ST)
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

	stamina->SetTextureRect({ 530, 118, int(stamina_current_w), 18});
}

void j1HUD::ActivateMenu()
{
	options->active = !options->active;
	returntogame->active = !returntogame->active;
	saveandexit->active = !saveandexit->active;


	App->game->pause = !App->game->pause;
}