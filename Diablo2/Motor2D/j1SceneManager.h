#ifndef __j1SCENEMANAGER_H__
#define __j1SCENEMANAGER_H__

#include "j1Module.h"
#include <list>

using namespace std;

class j1Scene;
class snIntro;
class snOutdoor1;
class snOutdoor2;
class snDungeon1;
class snDungeon2;
class snWin;

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

	// Methods
	void AddScene(j1Scene* scene);
	bool ChangeScene(j1Scene* new_scene);

	bool RandomLevel();

public:
	snIntro*	intro = NULL;
	snOutdoor1*	outdoor1 = NULL;
	snOutdoor2*	outdoor2 = NULL;
	snDungeon1* dungeon1 = NULL;
	snDungeon2* dungeon2 = NULL;
	snWin*		win = NULL;

	j1Scene* level1 = NULL;
	j1Scene* level2 = NULL;
	j1Scene* level3 = NULL;

private:
	list<j1Scene*>	scenes;
	j1Scene*		current_scene = NULL;
};

#endif // __j1SCENEMANAGER_H__

