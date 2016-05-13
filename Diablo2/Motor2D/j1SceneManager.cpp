#include "j1SceneManager.h"

#include "j1App.h"
#include "snIntro.h"
#include "snOutdoor1.h"
#include "snOutdoor2.h"
#include "snDungeon1.h"
#include "snDungeon2.h"
#include "snWin.h"

#include "j1Game.h"


j1SceneManager::j1SceneManager() : j1Module()
{
	intro = new snIntro();
	outdoor1 = new snOutdoor1();
	outdoor2 = new snOutdoor2();
	dungeon1 = new snDungeon1();
	dungeon2 = new snDungeon2();
	win = new snWin();

	AddScene(win);
	AddScene(intro);
	AddScene(outdoor1);
	AddScene(outdoor2);
	AddScene(dungeon1);
	AddScene(dungeon2);
}


j1SceneManager::~j1SceneManager()
{
}

// Called before render is available
bool j1SceneManager::Awake(pugi::xml_node& conf)
{
	current_scene = intro;
	return true;
}

// Called before the first frame
bool j1SceneManager::Start()
{
	current_scene->Start();
	return true;
}

//PreUpdate
bool j1SceneManager::PreUpdate()
{
	current_scene->PreUpdate();
	return true;
}

//Update
bool j1SceneManager::Update(float dt)
{
	current_scene->Update(dt);
	return true;
}

//PostUpdate
bool j1SceneManager::PostUpdate()
{
	current_scene->PostUpdate();
	return true;
}

// Called before quitting
bool j1SceneManager::CleanUp()
{
	current_scene->CleanUp();


	list<j1Scene*>::reverse_iterator item = scenes.rbegin();

	while (item != scenes.rend())
	{
		RELEASE(*item);
		++item;
	}

	scenes.clear();

	return true;
}

void j1SceneManager::AddScene(j1Scene* scene)
{
	scenes.push_back(scene);
}

// Changes the current scene
bool j1SceneManager::ChangeScene(j1Scene* new_scene)
{
	current_scene->UnLoad();

	//WARNING: this is purely provisional for the 0.2 version, HAS TO BE CHANGED, the in-game system and all the modules that are activcated there
	if (current_scene == intro)
	{
		//NOTE: may have to be changed in the future
		App->game->Init();
		App->game->Start();
	}

	if ((new_scene == intro && current_scene != win) || new_scene == win)
	{
		App->game->active = false;
		App->game->CleanUp();
	}
	//
	current_scene = new_scene;

	current_scene->Load();

	return true;
}

j1Scene* j1SceneManager::GetCurrentScene()
{
	return current_scene;
}

void j1SceneManager::RandomLevel()
{
	int level = rand() % 2;

	switch (level)
	{
	case 0:
		level1 = outdoor2;
		break;
	case 1:
		level1 = dungeon2;
		//ChangeScene(dungeon2);
		break;
	}


	if (level1 == outdoor2)
	{
		level2 = dungeon2;
		//ChangeScene(dungeon2);
	}
	else
	{
		level2 = outdoor2;
		//ChangeScene(outdoor2);
	}
}