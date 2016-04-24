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
	int skill1points;
	int skill2points;
	int skill3points;
	int skill4points;
	int skill5points;
	int skill6points;
	int skill7points;
	int skill8points;
	int skill9points;
	int skill10points;

	bool skill1_pressed = false;
	bool skill2_pressed = false;
	bool skill3_pressed = false;
	bool skill4_pressed = false;
	bool skill5_pressed = false;
	bool skill6_pressed = false;
	bool skill7_pressed = false;
	bool skill8_pressed = false;
	bool skill9_pressed = false;
	bool skill10_pressed = false;

	GuiImage* skilltree = NULL;
	GuiImage* skill1 = NULL;
	GuiImage* skill2 = NULL;
	GuiImage* skill3 = NULL;
	GuiImage* skill4 = NULL;
	GuiImage* skill5 = NULL;
	GuiImage* skill6 = NULL;
	GuiImage* skill7 = NULL;
	GuiImage* skill8 = NULL;
	GuiImage* skill9 = NULL;
	GuiImage* skill10 = NULL;
};


#endif