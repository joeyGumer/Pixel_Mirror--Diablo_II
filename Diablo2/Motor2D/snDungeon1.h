#ifndef _SNDUNGEON1_H
#define _SNDUNGEON1_H

#include "j1Scene.h"
#include "p2Point.h"
#include <list>

using namespace std;

struct Sprite;
struct SDL_Texture;
struct SDL_Rect;
class GuiElement;
class Entity;



class snDungeon1 : public j1Scene
{
public:
	// Constructor
	snDungeon1();

	// Destructor
	~snDungeon1();

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
	void AddEnemies();
	
private:


public:
	//NOTE: provisional.
	SDL_Texture* debug = NULL;

	list<Entity*>		entity_list;

	bool win;
};

#endif _SNDUNGEON1_H