#include "j1InputManager.h"
#include "j1App.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1FileSystem.h"
#include "j1Input.h"
#include "SDL\include\SDL.h"
#include "j1Gui.h"

j1InputManager::j1InputManager() : j1Module()
{
	name.create("input_manager");
}

// Destructor
j1InputManager::~j1InputManager()
{}

// Called when before render is available
bool j1InputManager::Awake(pugi::xml_node& conf)
{
	bool ret = true;

	//Loading shortcuts path xml
	inputs_file_path = conf.child("shortcuts_path").attribute("value").as_string();

	return ret;
}

// Call before first frame
bool j1InputManager::Start()
{
	bool ret = true;

	//TODO 4: Uncomment this to complete TODO 4
	//pop_up = App->gui->CreateImage({ 0, 0, 220, 250 }, 100, 100, App->input_manager);
	//LoadShortcutsInfo();

	return ret;
}

// Called before all Updates
bool j1InputManager::PreUpdate()
{
	bool ret = true;

	//TODO 2: Set active state on true if had been pressed any key that we are assigned to any shortcut (DOWN, UP, REPEAT)
	//You must do:
	//	- Check if queues are empty
	//	- Iterate each queue
	//	- Check each queue element with our shortcuts list (check shortcut command and type)
	//	- If this checks are true turn the right shortcut active = true

	//DOWN
	//Code with down queues here
	if (!App->input->down_queue.empty())
	{
		for (int i = 0; i < App->input->down_queue.size(); i++)
		{
			list<ShortCut*>::iterator it = shortcuts_list.begin();
			while (it != shortcuts_list.end())
			{
				if (App->input->down_queue.front() + i == (*it)->command && (*it)->type == DOWN)
					(*it)->active = true;
				++it;
			}
		}
	}
	//UP
	//Code with up queues here
	if (!App->input->up_queue.empty())
	{
		for (int i = 0; i < App->input->up_queue.size(); i++)
		{
			list<ShortCut*>::iterator it = shortcuts_list.begin();
			while (it != shortcuts_list.end())
			{
				if (App->input->up_queue.front() + i == (*it)->command && (*it)->type == UP)
					(*it)->active = true;
				++it;
			}
		}
	}
	//REPEAT
	//Code with repeat queues here
	if (!App->input->repeat_queue.empty())
	{
		for (int i = 0; i < App->input->repeat_queue.size(); i++)
		{
			list<ShortCut*>::iterator it = shortcuts_list.begin();
			while (it != shortcuts_list.end())
			{
				if (App->input->repeat_queue.front() + i == (*it)->command && (*it)->type == REPEAT)
					(*it)->active = true;
				++it;
			}
		}
	}

	return ret;
}

bool j1InputManager::Update(float dt)
{
	//http://stackoverflow.com/questions/17796921/how-to-handle-uppercase-keystrokes-in-sdl <----- NAIS

	bool ret = true;

	list<ShortCut*>::iterator it = shortcuts_list.begin();
	while (it != shortcuts_list.end())
	{
		if ((*it)->ready_to_change)
		{
			static SDL_Event event;

			SDL_WaitEvent(&event);

			if (event.type == SDL_KEYDOWN)
			{
				//NO ES COMPROBA SI M'ÉS D'UN SHORTCUT TENEN EL MATEIX COMMAND!!
				(*it)->command = SDL_GetScancodeName(event.key.keysym.scancode);
				ChangeShortcutCommand((*it));
				(*it)->ready_to_change = false;
			}
		}

		++it;
	}

	return ret;
}

// Called after all Updates
bool j1InputManager::PostUpdate()
{
	bool ret = true;

	//TODO 2: We must turn down all activity shortcuts again to reset their state
	list<ShortCut*>::iterator it = shortcuts_list.begin();

	while (it != shortcuts_list.end())
	{
		if ((*it)->active)
			(*it)->active = false;

		++it;
	}

	return ret;
}

// Called before quitting
bool j1InputManager::CleanUp()
{
	bool ret = true;

	shortcuts_list.clear();

	return ret;
}

void j1InputManager::ChangeShortcutCommand(ShortCut* shortcut)
{
	char n[20];
	sprintf_s(n, 20, "%c", shortcut->command);
	shortcut->command_label->SetText(n);

	shortcut->ready_to_change = true;
}