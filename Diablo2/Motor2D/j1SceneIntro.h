#ifndef __j1SCENEINTRO_H__
#define __j1SCENEINTRO_H__

#include "j1Module.h"

class j1SceneIntro : public j1Module
{
public:
	j1SceneIntro();

	//Destructor
	~j1SceneIntro();

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

#endif // __j1SCENEINTRO_H__

