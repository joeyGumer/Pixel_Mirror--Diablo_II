#include "hudPause.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1SceneManager.h"
#include "j1Game.h"
#include "snIntro.h"



hudPause::hudPause()
{

}

//Destructor
hudPause::~hudPause()
{

}

//Called before fist frame
bool hudPause::Start()
{
	main_menu = false;

	//Menu
	options = App->gui->AddGuiImage({ 310, 130 }, { 395, 71, 194, 31 }, NULL, this);
	options->interactable = true;
	options->active = false;
	hud_gui_elements.push_back(options);

	saveandexit = App->gui->AddGuiImage({ 145, 200 }, { 460, 0, 534, 35 }, NULL, this);
	saveandexit->interactable = true;
	saveandexit->active = false;
	hud_gui_elements.push_back(saveandexit);

	returntogame = App->gui->AddGuiImage({ 195, 270 }, { 994, 0, 438, 35 }, NULL, this);
	returntogame->interactable = true;
	returntogame->active = false;
	hud_gui_elements.push_back(returntogame);

	return true;
}

//Called before each loop iteration
bool hudPause::PreUpdate()
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
bool hudPause::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudPause::PostUpdate()
{
	return true;
}


//Called before quitting
bool hudPause::CleanUp()
{
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
void hudPause::OnEvent(GuiElement* element, GUI_Event even)
{
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

void hudPause::ActivateMenu()
{
	options->active = !options->active;
	returntogame->active = !returntogame->active;
	saveandexit->active = !saveandexit->active;

	App->game->pause = !App->game->pause;
}