#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

struct Sprite;
class GuiElement;
class GuiLabel;
class GuiImage;
class GuiInputBox;
class GuiSlider;


enum SCENE_TYPE
{
	OUTDOOR_1,
	OUTDOOR_2,
	DUNGEON_1,
	DUNGEON_2,
	DUNGEON_3,
	INTRO,
	WIN,
	LOSE
};

class j1Scene : public j1Module
{
public:

	// Constructor
	j1Scene(SCENE_TYPE tp)
	{
		type = tp;
	}

	// Destructor
	virtual ~j1Scene(){}

	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called before all Updates
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called before all Updates
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	//Called on certain event
	virtual void OnEvent(GuiElement* element, GUI_Event even){}

	//Load and unload NOTE:(maybe there's no need to make it virtual)
	virtual bool Load()
	{
		return true;
	}

	virtual bool UnLoad()
	{
		return true;
	}


	SCENE_TYPE type;

private:
};

#endif // __j1SCENE_H__