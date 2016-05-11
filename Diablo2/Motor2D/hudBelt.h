#ifndef _HUDBELT_H_
#define _HUDBELT_H_

#include "hudElement.h"

enum GUI_EVENT;
class j1HUD;
class GuiElement;
class GuiImage;
class GuiLabel;
class GuiInventory;
class j1Player;
class GuiSkill;

#define STAT_LOCAL_Y 34
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

	//Running On
	void RunningOn();

public:

	//Life
	float life_current_h;

	//Mana
	float mana_current_h;

	//Stamina
	float stamina_current_w;

	//Some buttons bools
	bool minipanel_pressed = false;
	bool attack1_pressed = false;
	bool attack2_pressed = false;
	bool inventorybutton_pressed = false;
	bool skilltreebutton_pressed = false;
	bool statsbutton_pressed = false;
	bool menubutton_pressed = false;
	bool minimapbutton_pressed = false;

	//Belt Gui Elements
	GuiImage* HUD = NULL;
	GuiImage* HUDornament = NULL;
	GuiImage* minipanel = NULL;
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
	GuiImage* inventorybutton = NULL;
	GuiImage* minimapbutton = NULL;
	GuiImage* game_menu = NULL;

	/*
	//---Skills options
	*/

	//Command
	GuiSkill* attack_right = NULL;
	GuiSkill* attack_left = NULL;

	//Left skills
	GuiSkill* left_basic_attack = NULL;


	//Right skills
	GuiSkill* right_basic_attack = NULL;
	GuiSkill* blood_arrow = NULL;

	

	//NOTE : labels for debug:
	GuiLabel* life_debug;
	GuiLabel* mana_debug;
	
	GuiInventory* inventory1 = NULL;
	GuiInventory* inventory2 = NULL;
	GuiInventory* inventory3 = NULL;
	GuiInventory* inventory4 = NULL;
	

	//Strict relation with the player
	j1Player* player;
};


#endif _HUDBELT_H_