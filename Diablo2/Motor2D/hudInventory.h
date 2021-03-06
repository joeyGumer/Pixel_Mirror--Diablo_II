#ifndef _HUDINVENTORY_H_
#define _HUDINVENTORY_H_

#include "hudElement.h"

class j1HUD;
class GuiElement;
class GuiImage;
class GuiInventory;
class GuiItem;
class j1Player;




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

	//Load/Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	void SaveItemData(GuiItem* item, pugi::xml_node&) const ;
	void LoadItemData(pugi::xml_node& node, GuiInventory* inv);

	//Activation/Desactivation
	void Activate();

	//NOTE: master of nope, but now i need it
	//Change it for an addItem
	bool AddItem(GuiItem* item, GuiInventory* inv = NULL);

public:

	j1Player* player;

	bool closebutton_pressed = false;

	GuiImage* background = NULL;
	GuiImage* closebutton = NULL;
	GuiInventory* inventory = NULL;

	GuiInventory* armor = NULL;

	GuiInventory* jewel = NULL;

	GuiInventory* ring1 = NULL;
	GuiInventory* ring2 = NULL;

	GuiInventory* stone1 = NULL;
	GuiInventory* stone2 = NULL;
	GuiInventory* stone3 = NULL;

	GuiInventory* rune1 = NULL;
	GuiInventory* rune2 = NULL;
	GuiInventory* rune3 = NULL;

	int no_item_feedback;
};

#endif _HUDINVENTORY_H_