#include "snIntro.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "snOutdoor1.h"
#include "j1Gui.h"
#include "j1Audio.h"


snIntro::snIntro() :j1Scene()
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

	pass = false;
	exit = false;

	//Gui Elements

	//Background
	background = App->gui->AddGuiImage({ 0, 0 }, {1829, 82, 800, 600}, NULL, this);
	intro_gui.push_back(background);
	
	//Play button
	play_button = App->gui->AddGuiButton({ 264, 260 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "Single player", NULL, this);
	intro_gui.push_back(play_button);
	
	//Exit button
	exit_button = App->gui->AddGuiButton({ 264, 450 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "Exit Diablo II", NULL, this);
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
		App->sm->ChangeScene(App->sm->outdoor1);
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
	//Play button
	if (play_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			play_button->button_image.SetTextureRect(play_button->click_tex);
			play_button->button_label.SetLocalPosition({ 50, 8 });
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			play_button->button_image.SetTextureRect(play_button->idle_tex);
			play_button->button_label.Center(true, true);
			pass = true;
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

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			exit_button->button_image.SetTextureRect(exit_button->click_tex);
			exit_button->button_label.SetLocalPosition({ 50, 8 });
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