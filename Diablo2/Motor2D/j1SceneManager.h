#ifndef __j1SCENEMANAGER_H__
#define __j1SCENEMANAGER_H__

#include "j1Module.h"
#include <list>
#include <vector>

using namespace std;

class j1Scene;
class snIntro;
class snOutdoor1;
class snOutdoor2;
class snDungeon1;
class snDungeon2;
class snDungeon3;
class snWin;
class snLose;
enum SCENE_TYPE;

class j1SceneManager : public j1Module
{
public:
	j1SceneManager();

	//Destructor
	~j1SceneManager();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Load/Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	//Load Game
	bool LoadGame();

	// Methods
	void AddScene(j1Scene* scene);
	bool ChangeScene(j1Scene* new_scene);

	j1Scene* GetCurrentScene();

	j1Scene* GetSceneByType(SCENE_TYPE tp);

	j1Scene* GetCurrentLevel();

	void RandomLevel();

public:
	snIntro*	intro = NULL;
	snOutdoor1*	outdoor1 = NULL;
	snOutdoor2*	outdoor2 = NULL;
	snDungeon1* dungeon1 = NULL;
	snDungeon2* dungeon2 = NULL;
	snDungeon3* dungeon3 = NULL;
	snWin*		win = NULL;
	snLose*     lose = NULL;

	j1Scene* level1 = NULL;
	j1Scene* level2 = NULL;
	j1Scene* level3 = NULL;

	bool	load_game = false;
	bool	loading_game = false;

	int level = 0;

	j1Scene*		current_scene = NULL;

private:
	vector<j1Scene*>	scenes;
};

#endif // __j1SCENEMANAGER_H__

