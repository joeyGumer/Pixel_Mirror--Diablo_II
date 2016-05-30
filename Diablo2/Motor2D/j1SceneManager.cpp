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
	//name.create("scene manager");
	name.create("sm");

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
	/*if (loading_game)
	{
		j1Scene* loaded_scene = GetCurrentLevel();

		if (loaded_scene)
		{
			ChangeScene(loaded_scene);
		}

		loading_game = false;
	}*/

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
		if (!loading_game)
		{
			App->game->Init();
			App->game->Start();
		}

	}

	if ((new_scene == intro && current_scene != win && current_scene != lose) || new_scene == win || new_scene == lose)
	{
		App->game->active = false;
		App->game->CleanUp();
	}
	else
	{
		if (!loading_game)
		{
			level++;
		}
	}

	//

	current_scene = new_scene;


	if (current_scene)
	{
		current_scene->LoadScene();
	}
	

	

	return true;
}

j1Scene* j1SceneManager::GetCurrentScene()
{
	return current_scene;
}

j1Scene* j1SceneManager::GetCurrentLevel()
{


	if (level == 2)
	{
		return level2;
	}
	else if (level == 1)
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

	pugi::xml_node lvl = levels.child("level_scene");
	pugi::xml_node lvl1, lvl2;
	

	for (int i = 0; lvl; lvl = lvl.next_sibling("level_scene"), i++)
	{
	
		if (i == 0)
		{
			SCENE_TYPE tp = (SCENE_TYPE)lvl.attribute("type").as_int();
			level1 = GetSceneByType(tp);
			lvl1 = lvl;
		}
	
		else if (i == 1)
		{
			SCENE_TYPE tp = (SCENE_TYPE)lvl.attribute("type").as_int();
			level2 = GetSceneByType(tp);
			lvl2 = lvl;
		}
	}

	level = levels.child("level").attribute("value").as_int();

	loading_game = true;

	j1Scene* loaded_scene = GetCurrentLevel();

	if (loaded_scene)
	{
		ChangeScene(loaded_scene);
	}

	if (level == 1)
	{
		((j1Module*)current_scene)->Load(lvl1);
	}
	else if (level == 2)
	{
		((j1Module*)current_scene)->Load(lvl2);
	}

	loading_game = false;

	return true;
}

bool j1SceneManager::Save(pugi::xml_node& node) const
{
	pugi::xml_node levels = node.append_child("levels");

	levels.append_child("level").append_attribute("value") = level;

	if (level1)
	{
		pugi::xml_node lvl1 = levels.append_child("level_scene");

		lvl1.append_attribute("type") = level1->type;

		if (current_scene == level1)
		{
			((j1Module*)current_scene)->Save(lvl1);

		}
	}
	
	if (level2)
	{
		pugi::xml_node lvl2 = levels.append_child("level_scene");

		lvl2.append_attribute("type") = level2->type;

		if (current_scene == level2)
		{
			((j1Module*)current_scene)->Save(lvl2);

		}
	}

	

	return true;
}


bool j1SceneManager::LoadGame()
{
	App->game->Init();
	App->game->Start();

	App->LoadGame("save_state");

	return true;
}