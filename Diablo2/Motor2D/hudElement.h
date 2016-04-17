#ifndef _HUDELEMENT_H_
#define _HUDELEMENT_H_

#include "j1Module.h"
#include <vector>

using namespace std;

class GuiElement;
enum GUI_Event;


class hudElement : public j1Module
{
public:
	
	hudElement(): j1Module()
	{

	}
	//Called before fist frame
	bool Start()
	{
		return true;
	}

	//Called before each loop iteration
	bool PreUpdate()
	{
		return true;
	}

	//Called each frame
	bool Update(float dt)
	{
		return true;
	}

	//Called after each loop iteration
	bool PostUpdate()
	{
		return true;
	}

	//Called before quitting
	bool CleanUp()
	{
		return true;
	}

	virtual void OnEvent(GuiElement* element, GUI_Event even)
	{
	
	}

	virtual void Activate()
	{
		active = !active;
	}

public:
	
	bool active;
	vector<GuiElement*> hud_gui_elements;
};

#endif _HUDELEMENT_H_