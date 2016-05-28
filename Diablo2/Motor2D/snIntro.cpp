#include "snIntro.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "snOutdoor1.h"
#include "snOutdoor2.h"
#include "snDungeon1.h"
#include "snDungeon2.h"
#include "snDungeon3.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Audio.h"



snIntro::snIntro() :j1Scene(INTRO)
{}


snIntro::~snIntro()
{}

// Called before render is available
bool snIntro::Awake(pugi::xml_node& conf)
{
	

	return true;
}

bool snIntro::Start()
{
	//Music
	//NOTE : deactivated for debugging mode
	//App->audio->PlayMusic("audio/music/introedit.ogg", 0);

	App->new_game = false;

	pass = false;
	load = false;
	exit = false;

	//Gui Elements

	//Background
	background = App->gui->AddGuiImage({ -95, -40 }, {1829, 82, 800, 600}, NULL, this);
	intro_gui.push_back(background);

	//Title animation
	if (title == NULL)
		title = App->tex->Load("gui/NewTitle.png");

	for (int i = 0; i < 6; i++)
	{
		logo.SetFrames(0, 0 + 170*i, 400, 170, 5, 0);
	}
	logo.loop = true;
	logo.speed = 0.2f;

	titleAnim = App->gui->AddGuiAnimation({ 115, 0 }, logo, title, NULL, this);
	intro_gui.push_back(titleAnim);

	//New button
	new_button = App->gui->AddGuiButton({ 181, 280 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "New Game", NULL, this);
	intro_gui.push_back(new_button);

	//Play button
	play_button = App->gui->AddGuiButton({ 181, 320 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "Load Game", NULL, this);
	intro_gui.push_back(play_button);
	if (!App->fs->SaveFileExists())
	{
		play_button->active = false;
	}

	//Controls button
	controls_button = App->gui->AddGuiButton({ 181, 360 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "CONTROLS", NULL, this);
	intro_gui.push_back(controls_button);

	//Exit button
	exit_button = App->gui->AddGuiButton({ 181, 400 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "ExiT Diablo II", NULL, this);
	intro_gui.push_back(exit_button);

	//-----------
	

	

	return true;
}

// PreUpdate
bool snIntro::PreUpdate()
{
	
	return true;
}

// Update
bool snIntro::Update(float dt)
{
	//Exit game quick
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		std::exit(0);
	}
	//Insert iterations for this scene here

	/*
	// When pressing SPACE it changes to the scene outdoor1
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == true)
	{
		//The scene manager changes the scene to outdoor1
		App->sm->ChangeScene(App->sm->outdoor1);
	}
	//
	*/
	if (pass == true)
	{
		if (App->fs->SaveFileExists())
		{
			App->fs->DeleteSaveFile();
		}

		App->new_game = true;

		App->sm->RandomLevel();
		if (App->sm->level1)
		{
			App->sm->ChangeScene(App->sm->level1);
		}
	}

	else if (load == true)
	{

		App->sm->LoadGame();
	}

	else if (exit == true)
	{
		std::exit(0);
	}



	return true;
}

// PostUpdate
bool snIntro::PostUpdate()
{
	//Logo animation
	
	return true;
}

// Called before quitting
bool snIntro::CleanUp()
{
	// NOTA : hacer función en UI que elimine un elemento de la lista(no por el nodo), quizas mejor aun si va por conjunto (para quitar todos los elementos de una escena
	//deletes the elements from the scene from the gui_elements list
	//maybe just by deactivating the iteration of this elements is a good way, who knows, ask ric

	for (list<GuiElement*>::iterator item = intro_gui.begin(); item != intro_gui.end(); item++)
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
	
	intro_gui.clear();
	
	return true;
}

void snIntro::OnEvent(GuiElement* element, GUI_Event even)
{	
	//NOTE clicking the button could charge the scene, now sets the bool pass to true and changes it, I don't think it's bad, but I don't know if the other way is better or not.
	if (new_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			new_button->button_image.SetTextureRect(play_button->click_tex);
			iPoint label_pos = new_button->button_label.GetLocalPosition();
			label_pos.x -= 4;
			label_pos.y += 2;
			new_button->button_label.SetLocalPosition(label_pos);
		}
		break;

		case EVENT_MOUSE_EXIT:
		{
			new_button->button_image.SetTextureRect(play_button->idle_tex);
			new_button->button_label.Center(true, true);
		}
		break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			new_button->button_image.SetTextureRect(play_button->idle_tex);
			new_button->button_label.Center(true, true);
			pass = true;
		}
		break;
		}
	}

	//Play button
	if (play_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			play_button->button_image.SetTextureRect(play_button->click_tex);
			iPoint label_pos = play_button->button_label.GetLocalPosition();
			label_pos.x -= 4;
			label_pos.y += 2;
			play_button->button_label.SetLocalPosition(label_pos);
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			play_button->button_image.SetTextureRect(play_button->idle_tex);
			play_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			play_button->button_image.SetTextureRect(play_button->idle_tex);
			play_button->button_label.Center(true, true);
			load = true;
		}
			break;
		}
	}
	if (controls_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			controls_button->button_image.SetTextureRect(controls_button->click_tex);
			controls_button->button_label.SetLocalPosition({ 75, 8 });
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			controls_button->button_image.SetTextureRect(controls_button->idle_tex);
			controls_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			controls_button->button_image.SetTextureRect(controls_button->idle_tex);
			controls_button->button_label.Center(true, true);
		}
			break;
		}
	}
	//Exit button
	if (exit_button == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			exit_button->button_image.SetTextureRect(exit_button->click_tex);
			//NOTE : put this coordinates at the config.
			exit_button->button_label.SetLocalPosition({ 50, 8 });
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			exit_button->button_image.SetTextureRect(exit_button->idle_tex);
			exit_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			exit_button->button_image.SetTextureRect(exit_button->idle_tex);
			exit_button->button_label.Center(true, true);
			exit = true;
		}
			break;

		}
	}
}

//Load/UnLoad, called when the scene changes
bool snIntro::Load()
{
	Start();
	return true;
}

bool snIntro::UnLoad()
{
	CleanUp();
	return true;
}