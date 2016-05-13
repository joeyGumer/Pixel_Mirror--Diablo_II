#ifndef _HUDMINIMAP_H_
#define _HUDMINIMAP_H_

#include "hudElement.h"
#include "SDL/include/SDL.h"
class j1HUD;
class GuiElement;
class GuiImage;
class GuiMiniMap;





class hudMiniMap : public hudElement
{
public:
	//Constructor
	hudMiniMap();

	//Destructor
	~hudMiniMap();

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

	//Activation/Desactivation
	void Activate();

	//NOTE: master of nope, but now i need it
	//Change it for an addItem
	//bool AddItem(GuiItem* item);

public:

	GuiMiniMap* minimap = NULL;
	
};


#endif _HUDMINIMAP_H_