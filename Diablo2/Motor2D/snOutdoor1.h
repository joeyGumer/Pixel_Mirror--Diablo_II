#ifndef _SNOUTDOOR1_H_
#define _SNOUTDOOR1_H_

#include "j1Scene.h"
#include "p2Point.h"
#include <list>

using namespace std;

class GuiImage;
class GuiElement;
class GuiButton;
class SDL_Texture;

class snOutdoor1 : public j1Scene
{
public:
	// Constructor
	snOutdoor1();

	// Destructor
	~snOutdoor1();

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

public:
	/*int lifey;
	int lifeh;
	int lifeypos;
	int manay;
	int manah;
	int manaypos;
	
private:
	bool menu_active;
	bool main_menu;
	bool keep_playing;
	bool runpressed;
	bool minipanelpressed;

	//In game menu elements -------
	GuiImage* options = NULL;
	GuiImage* saveandexit = NULL;
	GuiImage* returntogame = NULL;

	//HUD elements ----------------
	GuiImage* HUD = NULL;
	GuiImage* HUDback1 = NULL;
	GuiImage* HUDback2 = NULL;
	GuiImage* life = NULL;
	GuiImage* mana = NULL;
	GuiImage* runbutton = NULL;
	GuiImage* minipanelbutton = NULL;
	GuiImage* minipanel = NULL;
	GuiImage* attack1 = NULL;
	GuiImage* attack2 = NULL;*/

	list<GuiElement*> outdoor_gui;
};

#endif