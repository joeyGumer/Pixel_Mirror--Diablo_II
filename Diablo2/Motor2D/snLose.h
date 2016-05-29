#ifndef _SNLOSE_H_
#define _SNLOSE_H_

#include "j1Scene.h"
#include "j1Timer.h"
#include <list>
#include "j1Gui.h"

using namespace std;

class Entity;


class snLose : public j1Scene
{
public:
	// Constructor
	snLose();

	// Destructor
	~snLose();

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
	bool LoadScene();
	bool UnLoad();

	//Adding Enemies
	void AddEnemies();

private:


public:
	//NOTE: provisional.
	//SDL_Texture* back = NULL;
	j1Timer ret;

	GuiImage* loseback = NULL;

	list<GuiElement*> lose_gui;

};

#endif _SNLOSE_H_