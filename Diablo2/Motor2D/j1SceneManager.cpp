#include "j1SceneManager.h"

#include "j1App.h"
#include "snIntro.h"
#include "snOutdoor1.h"
#include "snOutdoor2.h"
#include "snDungeon1.h"
#include "snDungeon2.h"
#include "snDungeon3.h"
#include "snWin.h"
#include "snLose.h"

#include "j1Game.h"


j1SceneManager::j1SceneManager() : j1Module()
{
	intro = new snIntro();
	outdoor1 = new snOutdoor1();
	outdoor2 = new snOutdoor2();
	dungeon1 = new snDungeon1();
	dungeon2 = new snDungeon2();
	dungeon3 = new snDungeon3();
	win = new snWin();
	lose = new snLose();

	AddScene(win);
	AddScene(lose);
	AddScene(intro);
	AddScene(outdoor1);
	AddScene(outdoor2);
	AddScene(dungeon1);
	AddScene(dungeon2);
	AddScene(dungeon3);
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


	for (int i = 0; i < scenes.size(); i++)
	{
		RELEASE(scenes[i]);
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

	
	if (current_scene == intro)
	{
		//NOTE: may have to be changed in the future
		App->game->Init();
		App->game->Start();
	}

	if ((new_scene == intro && current_scene != win && current_scene != lose) || new_scene == win || new_scene == lose)
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

j1Scene* j1SceneManager::GetCurrentLevel()
{


	if (level2)
	{
		return level2;
	}
	else if (level1)
	{
		return level1;
	}
	else
		return NULL;
}

j1Scene* j1SceneManager::GetSceneByType(SCENE_TYPE tp)
{
	j1Scene* ret = NULL;


	for (int i = 0; i < scenes.size() ; i++)
	{
		if (scenes[i]->type == tp)
		{
			ret = scenes[i];
			break;
		}
	}

	return ret;
}



void j1SceneManager::RandomLevel()
{
	int level = rand() % 3;

	switch (level)
	{
	case 0:
		level1 = dungeon3;
		break;
	case 1:
		level1 = dungeon2;
		//ChangeScene(dungeon2);
		break;
	case 2:
		level1 = outdoor2;
		//ChangeScene(dungeon2);
		break;
	}

	int _level = rand() % 2;
	if (level1 == dungeon3)
	{
		switch (_level)
		{
		case 0:
			level2 = outdoor2;
			break;
		case 1:
			level2 = dungeon2;
			//ChangeScene(dungeon2);
			break;
		}
		//level2 = dungeon2;
		//ChangeScene(dungeon2);
	}
	else if (level1 == dungeon2)
	{
		switch (_level)
		{
		case 0:
			level2 = outdoor2;
			break;
		case 1:
			level2 = dungeon3;
			//ChangeScene(dungeon2);
			break;
		}
		//level2 = dungeon3;
		//ChangeScene(outdoor2);
	}
	else if (level1 == outdoor2)
	{
		switch (_level)
		{
		case 0:
			level2 = dungeon2;
			break;
		case 1:
			level2 = dungeon3;
			//ChangeScene(dungeon2);
			break;
		}
		//level2 = dungeon3;
		//ChangeScene(outdoor2);
	}
}

bool j1SceneManager::Load(pugi::xml_node& node)
{
	pugi::xml_node levels = node.child("levels");

	pugi::xml_node lvl = levels.child("level");

	for (; lvl; lvl = lvl.next_sibling("level"))
	{
		if (!level1)
		{
			SCENE_TYPE tp = (SCENE_TYPE)lvl.attribute("type").as_int();
			level1 = GetSceneByType(tp);
		}
		else if (!level2)
		{
			SCENE_TYPE tp = (SCENE_TYPE)lvl.attribute("type").as_int();
			level2 = GetSceneByType(tp);
		}
	}

	return true;
}

bool j1SceneManager::Save(pugi::xml_node& node) const
{
	pugi::xml_node levels = node.append_child("levels");

	if (level1)
	{
		pugi::xml_node lvl1 = node.append_child("level");

		lvl1.append_attribute("type") = level1->type;
	}
	
	if (level2)
	{
		pugi::xml_node lvl2 = node.append_child("level");

		lvl2.append_attribute("type") = level2->type;
	}

	return true;
}