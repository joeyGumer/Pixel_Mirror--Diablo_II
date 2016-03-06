#ifndef __SNINTRO_H__
#define __SNINTRO_H__

#include "j1Scene.h"

class snIntro : public j1Scene
{
public:
	// Constructor
	snIntro();

	// Destructor
	~snIntro();

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
};

#endif // __SNINTRO_H__

