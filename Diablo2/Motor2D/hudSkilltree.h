#ifndef _HUDSKILLTREEE_H_
#define _HUDSKILLTREE_H_

#include "hudElement.h"

class j1HUD;
class GuiElement;
class GuiImage;


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

	int skillpoints;
	int lionpoints;
	int clawpoints;
	int swordspoints;
	int handpoints;
	int starpoints;
	int fireballpoints;
	int projectilespoints;
	int manpoints;
	int cogpoints;
	int heartjawpoints;
	int batwingpoints;
	int wolfpoints;
	int fangspoints;
	int bigjawpoints;
	int bloodmanpoints;

	bool lion_pressed = false;
	bool claw_pressed = false;
	bool swords_pressed = false;
	bool hand_pressed = false;
	bool star_pressed = false;
	bool fireball_pressed = false;
	bool projectiles_pressed = false;
	bool man_pressed = false;
	bool cog_pressed = false;
	bool heartjaw_pressed = false;
	bool batwing_pressed = false;
	bool wolf_pressed = false;
	bool fangs_pressed = false;
	bool bigjaw_pressed = false;
	bool bloodman_pressed = false;

	GuiImage* martialblood = NULL;
	GuiImage* bloodspells = NULL;
	GuiImage* nightsummoning = NULL;
	GuiImage* nightbutton = NULL;
	GuiImage* bloodbutton = NULL;
	GuiImage* martialdeletebutton = NULL;
	GuiImage* blooddeletebutton = NULL;
	GuiImage* nightdeletebutton = NULL;
	GuiImage* lion = NULL;
	GuiImage* claw = NULL;
	GuiImage* swords = NULL;
	GuiImage* hand = NULL;
	GuiImage* star = NULL;
	GuiImage* fireball = NULL;
	GuiImage* projectiles = NULL;
	GuiImage* man = NULL;
	GuiImage* cog = NULL;
	GuiImage* heartjaw = NULL;
	GuiImage* batwing = NULL;
	GuiImage* wolf = NULL;
	GuiImage* fangs = NULL;
	GuiImage* bigjaw = NULL;
	GuiImage* bloodman = NULL;

	GuiLabel* skillpoints_label;
};


#endif