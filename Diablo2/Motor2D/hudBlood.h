#ifndef _HUDBLOOD_H_
#define _HUDBLOOD_H_

#include "hudElement.h"

class j1Player;
class GuiLabel;
enum TextColor;
class hudBlood : public hudElement
{
public:
	//Constructor
	hudBlood();

	//Destructor
	~hudBlood();

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

	//Utils
	void IncreaseBlood(int blood);
	void SetBlood(int blood);

public:

	int			blood_current;
	int         blood_tmp;
	bool        message_get;
	j1Player*	player;

	GuiLabel*	blood_label;
	GuiLabel*   hey_listen;
};

#endif