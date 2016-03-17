#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"

//NOTE: player speed, put it at the config file
#define PLAYER_SPEED 200.0f;

struct SDL_Texture;

class j1Player : public j1Module
{
public:
	j1Player();

	//Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called the first frame
	bool Start();

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	// Called each loop iteration
	void Draw() const;

	// Called before quitting
	bool CleanUp();

public:

	iPoint player_pos;
	//NOTE: for testing purposes
	SDL_Texture* character = NULL;
};

#endif // __j1PLAYER_H__

