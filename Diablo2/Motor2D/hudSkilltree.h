#ifndef _HUDSKILLTREE_H_
#define _HUDSKILLTREE_H_

#include "hudElement.h"
#include "p2Point.h"


class j1HUD;
class GuiElement;
class GuiImage;
class GuiSkill;
class j1Player;


class hudSkilltree : public hudElement
{
public:
	//Constructor
	hudSkilltree();

	//Destructor
	~hudSkilltree();

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
	void Activate();


public:

	j1Player* player = NULL;

	int skillpoints;

	bool martialdeletebutton_pressed = false;

	GuiImage* martialblood = NULL;
	GuiImage* bloodspells = NULL;
	GuiImage* nightsummoning = NULL;
	GuiImage* nightbutton = NULL;
	GuiImage* bloodbutton = NULL;
	GuiImage* martialdeletebutton = NULL;
	GuiImage* blooddeletebutton = NULL;
	GuiImage* nightdeletebutton = NULL;
	GuiImage* skill_points_img = NULL;


	//Blood spells
	GuiSkill* blood_arrow = NULL;
	GuiSkill* vampire_breath = NULL;
	GuiSkill* blood_bomb = NULL;
	GuiSkill* red_feast = NULL;
	GuiSkill* heard_of_bats = NULL;

	//Martial blood
	GuiSkill* stinging_strike = NULL;
	GuiSkill* wild_talon = NULL;
	GuiSkill* bat_strike = NULL;
	GuiSkill* soul_of_ice = NULL;
	GuiSkill* krobus_arts = NULL;
	//GuiSkill* heard_of_bats = NULL;

	//Night Passives
	GuiSkill* clotted_blood_skin = NULL;
	GuiSkill* raise_wolf = NULL;
	GuiSkill* raise_blood_hawk = NULL;
	GuiSkill* blood_golem = NULL;
	GuiSkill* bat_girl = NULL;

	GuiLabel* price1;
	GuiLabel* price2;
	GuiLabel* price3;
	GuiLabel* price4;
	GuiLabel* price5;
	GuiLabel* price6;
	GuiLabel* price7;
	GuiLabel* price8;
	GuiLabel* price9;
	GuiLabel* price10; 
	GuiLabel* price11;
	GuiLabel* price12;
	GuiLabel* price13;
	GuiLabel* price14;
	GuiLabel* price15;



	GuiLabel* skillpoints_label;
	vector<GuiText*> texts;
	vector<GuiSkill*> skills;
};


#endif _HUDSKILLTREE_H_