#ifndef _HUDPAUSE_H_
#define _HUDPAUSE_H_

#include "hudElement.h"

class j1HUD;
class GuiElement;
class GuiImage;




class hudPause : public hudElement
{
public:
	//Constructor
	hudPause();

	//Destructor
	~hudPause();

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

	//Called when there's a gui event
	void OnEvent(GuiElement* element, GUI_Event even);

	
	//Utils
	void ActivateMenu();

public:

	bool main_menu;

	//In game menu elements -------
	GuiImage* options = NULL;
	GuiImage* saveandexit = NULL;
	GuiImage* returntogame = NULL;
};


#endif _HUDPAUSE_H_