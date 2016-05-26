#ifndef __j1GAME_H__
#define __j1GAME_H__

#include "j1Module.h"
#include "p2Point.h"
#include <list>

using namespace std;

class j1Player;
class j1HUD;
class j1EntityManager;

class j1Game : public j1Module
{
public:
	j1Game();

	//Destructor
	~j1Game();

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

	void Draw();

	//Utils
	void AddModule(j1Module* module);

	//Drops an item
	void DropItem(iPoint pos);

	//Load/Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:
	//Modules

	j1Player*			player = NULL;
	j1HUD*				HUD = NULL;
	j1EntityManager*	em = NULL;

	int base_no_drop = 60;
	int base_common_drop = 25;
	int base_rare_drop = 10;
	int base_legendary_drop = 5;

	bool        pause = false;

private:
	list<j1Module*>	game_modules;
};

#endif __j1GAME_H__