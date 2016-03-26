#include "snOutdoor1.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1SceneManager.h"
#include "snIntro.h"
#include "j1Map.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"

using namespace std;

// Constructor
snOutdoor1::snOutdoor1() : j1Scene()
{
	name.create("outdoor1");
}

// Destructor
snOutdoor1::~snOutdoor1()
{}

// Called before render is available
bool snOutdoor1::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called the first frame
bool snOutdoor1::Start()
{
	/*// Some variables for the in game menu ----
	menu_active = false;
	keep_playing = false;
	main_menu = false;
	//Some variables for the HUD
	runpressed = false;
	minipanelpressed = false;
	lifey = 117;
	lifeh = 80;
	lifeypos = 509;
	manay = 117;
	manah = 80;
	manaypos = 509;

	//HUD ----------------------------------------
	HUDback1 = App->gui->AddGuiImage({ 34, 536 }, { 362, 226, 76, 53 }, NULL, this);
	outdoor_gui.push_back(HUDback1);

	HUDback2 = App->gui->AddGuiImage({ 690, 536 }, { 437, 226, 80, 53 }, NULL, this);
	outdoor_gui.push_back(HUDback2);

	life = App->gui->AddGuiImage({ 29, 509 }, { 370, 117, 81, 80 }, NULL, this);
	outdoor_gui.push_back(life);

	mana = App->gui->AddGuiImage({ 690, 509 }, { 450, 117, 80, 80 }, NULL, this);
	outdoor_gui.push_back(mana);

	HUD = App->gui->AddGuiImage({ 0, 499 }, { 0, 331, 800, 103 }, NULL, this);
	outdoor_gui.push_back(HUD);

	runbutton = App->gui->AddGuiImage({ 254, 572 }, { 148, 279, 18, 22 }, NULL, this);
	runbutton->interactable = true;
	outdoor_gui.push_back(runbutton);

	minipanelbutton = App->gui->AddGuiImage({ 391, 562 }, { 337, 252, 16, 27 }, NULL, this);
	minipanelbutton->interactable = true;
	outdoor_gui.push_back(minipanelbutton);

	attack1 = App->gui->AddGuiImage({115, 553}, { 97, 279, 52, 49 }, NULL, this);
	attack1->interactable = true;
	outdoor_gui.push_back(attack1);

	attack2 = App->gui->AddGuiImage({633, 553}, { 97, 279, 52, 49 }, NULL, this);
	attack2->interactable = true;
	outdoor_gui.push_back(attack2);
	//HUD end-------------------------------------
	*/


	//Music
	//NOTE : deactivated for debugging
	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	//Map
	App->map->Load("test_map_swamp.tmx");

	return true;
}

// PreUpdate
bool snOutdoor1::PreUpdate()
{
	return true;
}

// Update
bool snOutdoor1::Update(float dt)
{	
	/*//HUD's logic ----------------------------------------------------
	// ---------------------------- LIFE -----------------------------
	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_REPEAT)
	{    
		if (lifey == 196)
		{
			lifey = lifey;
			lifeh = lifeh;
			lifeypos = lifeypos;
			life->SetTextureRect({ 370, lifey, 81, lifeh });
			life->SetLocalPosition({ 29, lifeypos });
		}
		else
		{
			lifey = lifey + 1;
			lifeh = lifeh - 1;
			lifeypos = lifeypos + 1;
			life->SetTextureRect({ 370, lifey, 81, lifeh });
			life->SetLocalPosition({ 29, lifeypos });
		}
		
	}

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_REPEAT)
	{
		if (lifey == 117)
		{
			lifey = lifey;
			lifeh = lifeh;
			lifeypos = lifeypos;
			life->SetTextureRect({ 370, lifey, 81, lifeh });
			life->SetLocalPosition({ 29, lifeypos });
		}
		else
		{
			lifey = lifey - 1;
			lifeh = lifeh + 1;
			lifeypos = lifeypos - 1;
			life->SetTextureRect({ 370, lifey, 81, lifeh });
			life->SetLocalPosition({ 29, lifeypos });
		}
	}
	// ---------------------------- MANA -----------------------------
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (manay == 196)
		{
			manay = manay;
			manah = manah;
			manaypos = manaypos;
			mana->SetTextureRect({ 450, manay, 80, manah });
			mana->SetLocalPosition({ 690, manaypos });
		}
		else
		{
			manay = manay + 1;
			manah = manah - 1;
			manaypos = manaypos + 1;
			mana->SetTextureRect({ 450, manay, 80, manah });
			mana->SetLocalPosition({ 690, manaypos });
		}

	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (manay == 117)
		{
			manay = manay;
			manah = manah;
			manaypos = manaypos;
			mana->SetTextureRect({ 450, manay, 80, manah });
			mana->SetLocalPosition({ 690, manaypos });
		}
		else
		{
			manay = manay - 1;
			manah = manah + 1;
			manaypos = manaypos - 1;
			mana->SetTextureRect({ 450, manay, 80, manah });
			mana->SetLocalPosition({ 690, manaypos });
		}
	}
	//HUD's logic end ------------------------------------------------

	//In-game menu ------------------------------------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && menu_active == false)
	{
		menu_active = true;
		
		options = App->gui->AddGuiImage({ 310, 130 }, { 395, 71, 194, 31 }, NULL, this);
		options->focusable = true;
		options->interactable = true;
		outdoor_gui.push_back(options);

		saveandexit = App->gui->AddGuiImage({ 145, 200 }, { 460, 0, 534, 35 }, NULL, this);
		saveandexit->focusable = true;
		saveandexit->interactable = true;
		outdoor_gui.push_back(saveandexit);

		returntogame = App->gui->AddGuiImage({ 195, 270 }, { 994, 0, 438, 35 }, NULL, this);
		returntogame->focusable = true;
		returntogame->interactable = true;
		outdoor_gui.push_back(returntogame);
	}
	//In-game menu end ---------------------------------------------------------------------

	else if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && menu_active == true)
	{
		menu_active = false;
		CleanUp();
	}

	else if (keep_playing == true)
	{
		App->sm->ChangeScene(App->sm->outdoor1);
	}

	else if (main_menu == true)
	{
		App->sm->ChangeScene(App->sm->intro);
	}
	*/
	//Map
	App->map->Draw();

	//Player
	
	App->player->Draw();
	

	//Camera
	//Free movement only avaliable on debug mode
	/*
	if (App->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			App->render->camera.x -= floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			App->render->camera.x += floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			App->render->camera.y -= floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			App->render->camera.y += floor(CAM_SPEED*dt);
		}
	}*/

	return true;
}

// PostUpdate
bool snOutdoor1::PostUpdate()
{
	return true;
}

// Called before quitting
bool snOutdoor1::CleanUp()
{
	/*for (list<GuiElement*>::iterator item = outdoor_gui.begin(); item != outdoor_gui.end(); item++)
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

	outdoor_gui.clear();*/

	return true;
}

// Called on certain event
void snOutdoor1::OnEvent(GuiElement* element, GUI_Event even)
{
	//HUD -------------------------------------
	//Run button
	/*if (runbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (runpressed == false)
			{
				runpressed = true;
				runbutton->SetTextureRect({ 148, 300, 18, 22 });
			}
			else
			{
				runpressed = false;
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
			if (minipanelpressed == false)
			{
				minipanelpressed = true;
				minipanelbutton->SetTextureRect({ 322, 252, 16, 27 });
				minipanel = App->gui->AddGuiImage({ 322, 529 }, { 169, 252, 154, 27 }, NULL, this);
				outdoor_gui.push_back(minipanel);
			}
			else
			{
				minipanelpressed = false;
				minipanelbutton->SetTextureRect({ 337, 252, 16, 27 });
				//NOTE: Delete minipanel :'^(
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
			keep_playing = true;
		break;
		}
	}*/
}
//Game menu end --------------------------------

//Load
bool snOutdoor1::Load()
{
	Start();
	return true;
}

//UnLoad
bool snOutdoor1::UnLoad()
{
	CleanUp();
	return true;
}