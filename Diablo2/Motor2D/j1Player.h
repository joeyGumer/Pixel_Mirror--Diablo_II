#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"

class j1Player : public j1Module
{
public:
	j1Player();

	//Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();
};

#endif // __j1PLAYER_H__

