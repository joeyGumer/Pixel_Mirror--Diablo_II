#include "hudPause.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1SceneManager.h"
#include "j1Game.h"
#include "snIntro.h"
#include "j1FileSystem.h"



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
	active = true;
	//Menu

	saveandexit = App->gui->AddGuiImage({ 45, 180 }, { 460, 0, 534, 35 }, NULL, this);
	saveandexit->interactable = true;
	saveandexit->active = false;
	hud_gui_elements.push_back(saveandexit);

	returntogame = App->gui->AddGuiImage({ 95, 250 }, { 994, 0, 438, 35 }, NULL, this);
	returntogame->interactable = true;
	returntogame->active = false;
	hud_gui_elements.push_back(returntogame);

	return true;
}

//Called before each loop iteration
bool hudPause::PreUpdate()
{
	if (App->fs->SaveFileExists() && main_menu)
	{
		if (!App->want_to_save)
		{
			ActivateMenu();
			App->sm->ChangeScene(App->sm->intro);
		}
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
		case EVENT_MOUSE_LEFTCLICK_UP:
			main_menu = true;
			App->SaveGame("save_state");
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
	returntogame->active = !returntogame->active;
	saveandexit->active = !saveandexit->active;

	App->game->pause = !App->game->pause;
}