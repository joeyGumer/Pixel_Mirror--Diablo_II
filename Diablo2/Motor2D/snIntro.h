#ifndef __SNINTRO_H__
#define __SNINTRO_H__

#include "j1Scene.h"
#include <list>

using namespace std;

class GuiImage;
class GuiElement;
class GuiButton;

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
	

private:
	
	bool pass;
	bool exit;

	//Ui elements
	GuiButton* play_button = NULL;
	GuiButton* exit_button = NULL;
	GuiImage* background = NULL;

	//NOTE : added this list to iterate easily the gui_elements of the scene. Ask ric about a more optimal way to control the UI
	//NOTE: do the button class so it can have the diferent images and even a label, so it doesn?t interfere with the rest of the ui
	list<GuiElement*> intro_gui;
};

#endif // __SNINTRO_H__

