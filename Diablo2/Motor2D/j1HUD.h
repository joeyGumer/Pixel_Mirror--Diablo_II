#ifndef _j1HUD_H_
#define _j1HUD_H_

#include "j1Module.h"
#include <list>

using namespace std;

#define STAT_LOCAL_Y 33
#define STAT_TEX_Y 196
#define STAT_MAX_H float(78)


enum GUI_Event;
class GuiElement;
class GuiImage;
class GuiLabel;

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

	//Utils
	void SetLife(int max_HP, int HP);
	void SetMana(int max_MP, int MP);

private:
	
	//Life
	float life_current_h;

	//Mana
	float mana_current_h;

	bool menu_active;
	bool main_menu;
	bool keep_playing;
	bool run_pressed = false;
	bool minipanel_pressed = false;

	//In game menu elements -------
	GuiImage* options = NULL;
	GuiImage* saveandexit = NULL;
	GuiImage* returntogame = NULL;

	//NOTE : lots of this  are unnecesary here
	//HUD elements ----------------
	GuiImage* HUD = NULL;
	GuiImage* HUDback1 = NULL;
	GuiImage* HUDback2 = NULL;
	GuiImage* life = NULL;
	GuiImage* mana = NULL;
	GuiImage* life_holder = NULL;
	GuiImage* mana_holder = NULL;
	GuiImage* runbutton = NULL;
	GuiImage* minipanelbutton = NULL;
	GuiImage* minipanel = NULL;
	GuiImage* attack1 = NULL;
	GuiImage* attack2 = NULL;

	//NOTE : labels for debug:
	GuiLabel* life_debug;
	GuiLabel* mana_debug;

	list<GuiElement*> HUD_elements;
};

#endif _GUIHUD_H_