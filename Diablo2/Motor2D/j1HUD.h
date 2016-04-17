#ifndef _j1HUD_H_
#define _j1HUD_H_

#include "j1Module.h"
#include <vector>

using namespace std;

enum GUI_Event;

class hudElement;
class hudBelt;
class hudPause;
class hudInventory;


class j1HUD : public j1Module
{
public:
	j1HUD();

	~j1HUD();
	//Called before fist frame
	bool Start();

	//Called before each loop iteration
	bool PreUpdate();

	//Called each frame
	bool Update(float dt);

	//Called after each loop iteration
	bool PostUpdate();
	
	//Called before quitting
	bool CleanUp();

	//Called when there's a GUI event
	void OnEvent(GuiElement* element, GUI_Event even);

private:

public:
	//HUD main belt
	hudBelt* belt = NULL;
	hudPause* pause_menu = NULL;
	hudInventory* inventory = NULL;

	vector<hudElement*> HUD_elements;
};

#endif _j1HUD_H_