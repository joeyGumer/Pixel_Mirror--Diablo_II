#ifndef _SNWIN_H_
#define _SNWIN_H_

#include "j1Scene.h"
#include "j1Timer.h"
#include <list>
#include "j1Gui.h"

using namespace std;

class Entity;


class snWin : public j1Scene
{
public:
	// Constructor
	snWin();

	// Destructor
	~snWin();

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
	//SDL_Texture* back = NULL;
	j1Timer ret;

	GuiImage* winback = NULL;

	list<GuiElement*> win_gui;
};

#endif _SNWIN_