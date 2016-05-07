#ifndef _HUDINVENTORY_H_
#define _HUDINVENTORY_H_

#include "hudElement.h"

class j1HUD;
class GuiElement;
class GuiImage;
class GuiInventory;
class GuiItem;




class hudInventory : public hudElement
{
public:
	//Constructor
	hudInventory();

	//Destructor
	~hudInventory();

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
	bool AddItem(GuiItem* item);

public:

	GuiImage* background = NULL;
	GuiInventory* inventory = NULL;
	

};


#endif _HUDINVENTORY_H_