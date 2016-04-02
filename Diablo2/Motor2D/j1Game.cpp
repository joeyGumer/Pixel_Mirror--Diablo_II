#include "j1App.h"
#include "j1Game.h"
#include "j1Player.h"
#include "j1HUD.h"


j1Game::j1Game() : j1Module()
{
	//Init modules
	player	= new j1Player();
	HUD		= new j1HUD();

	//Add modules to the list
	AddModule(player);
	AddModule(HUD);
}

//Destructor
j1Game::~j1Game()
{
	list<j1Module*>::reverse_iterator item = game_modules.rbegin();

	while (item != game_modules.rend())
	{
		RELEASE(*item);
		++item;
	}

	game_modules.clear();
}

// Called before render is available
bool j1Game::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called before the first frame
bool j1Game::Start()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Start();
	}

	return true;
}

//PreUpdate
bool j1Game::PreUpdate()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->PreUpdate();
	}

	return true;
}

//Update
bool j1Game::Update(float dt)
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		if (!pause)
			(*item)->Update(dt);

		(*item)->Draw();
	}


	return true;
}

//PostUpdate
bool j1Game::PostUpdate()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->PostUpdate();
	}

	return true;
}

// Called before quitting
bool j1Game::CleanUp()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->CleanUp();
	}

	return true;
}

void j1Game::Draw()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Draw();
	}
}

void j1Game::AddModule(j1Module* module)
{
	module->Init();
	game_modules.push_back(module);
}