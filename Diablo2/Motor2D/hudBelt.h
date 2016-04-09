#ifndef _HUDBELT_H_
#define _HUDBELT_H_

#include "hudElement.h"

enum GUI_EVENT;
class j1HUD;
class GuiElement;
class GuiImage;
class GuiLabel;


#define STAT_LOCAL_Y 33
#define STAT_TEX_Y 196
#define STAT_MAX_H float(78)
#define STAT_MAX_W float(102)

//NOTE : Do HUD Elements
class hudBelt : public hudElement
{
public:
	//Constructor
	hudBelt();

	//Destructor
	~hudBelt();

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
	void SetLife(int max_HP, int HP);
	void SetMana(int max_MP, int MP);
	void SetStamina(int max_ST, int ST);

public:

	//Life
	float life_current_h;

	//Mana
	float mana_current_h;

	//Stamina
	float stamina_current_w;

	//Some buttons bools
	bool run_pressed = false;
	bool minipanel_pressed = false;
	bool attack1_pressed = false;
	bool attack2_pressed = false;

	//Belt Gui Elements
	GuiImage* HUD = NULL;
	GuiImage* HUDback1 = NULL;
	GuiImage* HUDback2 = NULL;
	GuiImage* life = NULL;
	GuiImage* mana = NULL;
	GuiImage* stamina = NULL;
	GuiImage* life_holder = NULL;
	GuiImage* mana_holder = NULL;
	GuiImage* runbutton = NULL;
	GuiImage* minipanelbutton = NULL;
	GuiImage* stats = NULL;
	GuiImage* skilltree = NULL;
	GuiImage* inventory = NULL;
	GuiImage* map = NULL;
	GuiImage* message_log = NULL;
	GuiImage* search_log = NULL;
	GuiImage* game_menu = NULL;
	GuiImage* attack1 = NULL;
	GuiImage* attack2 = NULL;
	GuiImage* skill11 = NULL;
	GuiImage* skill12 = NULL;
	GuiImage* skill13 = NULL;
	GuiImage* skill21 = NULL;
	GuiImage* skill22 = NULL;
	GuiImage* skill23 = NULL;

	//NOTE : labels for debug:
	GuiLabel* life_debug;
	GuiLabel* mana_debug;
};


#endif _HUDBELT_H_