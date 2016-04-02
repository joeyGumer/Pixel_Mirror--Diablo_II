#include "j1SceneManager.h"

#include "j1App.h"
#include "snIntro.h"
#include "snOutdoor1.h"
#include "j1Game.h"


j1SceneManager::j1SceneManager() : j1Module()
{
	intro = new snIntro();
	outdoor1 = new snOutdoor1();

	AddScene(intro);
	AddScene(outdoor1);
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

	if (new_scene == intro)
	{
		App->game->active = false;
		App->game->CleanUp();
	}
	//
	current_scene = new_scene;

	current_scene->Load();

	return true;
}