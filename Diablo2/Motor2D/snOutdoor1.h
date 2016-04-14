#ifndef _SNOUTDOOR1_H_
#define _SNOUTDOOR1_H_

#include "j1Scene.h"
#include "p2Point.h"
#include <list>

using namespace std;


struct Sprite;
struct SDL_Texture;
struct SDL_Rect;
class GuiImage;
class GuiElement;
class GuiButton;



class snOutdoor1 : public j1Scene
{
public:
	// Constructor
	snOutdoor1();

	// Destructor
	~snOutdoor1();

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
//NOTE: Test Sprite Cow movment WASD
private:

	//void PlayerInput(float dt);

public:
	//NOTE: provisional.
	SDL_Texture* debug = NULL;

	list<GuiElement*> outdoor_gui;

	
	//NOTE: Test Sprite 
	Sprite* sprite_cow;
	SDL_Rect* pos_cow;
	SDL_Rect* sect_cow;
	
};

#endif