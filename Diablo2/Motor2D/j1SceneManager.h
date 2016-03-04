#ifndef __j1SCENEMANAGER_H__
#define __j1SCENEMANAGER_H__

#include "j1Module.h"

class j1SceneManager : public j1Module
{
public:
	j1SceneManager();

	//Destructor
	~j1SceneManager();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
};

#endif // __j1SCENEMANAGER_H__

