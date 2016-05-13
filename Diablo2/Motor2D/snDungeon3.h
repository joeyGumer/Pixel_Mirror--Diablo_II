#ifndef _SNDUNGEON3_H
#define _SNDUNGEON3_H

#include "j1Scene.h"
#include "p2Point.h"
#include <list>

using namespace std;

struct Sprite;
struct SDL_Texture;
struct SDL_Rect;
class GuiElement;
class Entity;



class snDungeon3 : public j1Scene
{
public:
	// Constructor
	snDungeon3();

	// Destructor
	~snDungeon3();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called the first frame
	bool Start();

	// PreUpdate
	bool PreUpdate();

	// Update
	bool Update(float dt);

	// PostUpdate
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Called on certain event
	void OnEvent(GuiElement* element, GUI_Event even);

	//Load/UnLoad, called when the scene changes
	bool Load();
	bool UnLoad();

	//Adding Enemies
	Entity* AddEnemy(iPoint pos);
	Entity* AddBoss(iPoint pos);
	void AddPortal(iPoint pos);

	//Spawn player
	void SpawnPlayer();

	//DropItem
	void DropItem(iPoint pos);

private:


public:
	//NOTE: provisional.
	SDL_Texture* debug = NULL;
	SDL_Texture* debug2 = NULL;
	list<Entity*>		entity_list;

	iPoint portal_spawn;

	bool win;
};

#endif