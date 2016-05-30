#ifndef __SNINTRO_H__
#define __SNINTRO_H__

#include "j1Scene.h"
#include <list>
#include "Animation.h"

using namespace std;

class GuiImage;
class GuiElement;
class GuiButton;
class GuiAnimation;
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
	bool LoadScene();
	bool UnLoad();

	//Reprogramable Keys
	//------------------------------------------

	bool LoadShortcutsInfo();

	//Refresh commands once have been changed
	//void ChangeShortcutCommand(ShortCut* shortcut);

	//------------------------------------------
	

private:
	
	bool shorcuts_loaded = false;

	bool pass;
	bool exit;
	bool load;

	//Ui elements
	GuiImage* pixelmirror_logo = NULL;
	GuiLabel* blizzard = NULL;
	GuiLabel* UPC = NULL;
	GuiLabel* blood = NULL;
	GuiLabel* project = NULL;
	GuiButton* play_button = NULL;
	GuiButton* new_button = NULL;
	GuiButton* controls_button = NULL;
	GuiButton* exit_button = NULL;
	GuiImage* background = NULL;
	GuiImage* controls_window = NULL;
	GuiAnimation* titleAnim = NULL;
	SDL_Texture* title = NULL;
	Animation logo;
	GuiLabel* primary_skill = NULL;
	GuiLabel* secondary_skill = NULL;
	GuiLabel* potion = NULL;
	GuiLabel* potion_two = NULL;
	GuiLabel* potion_three = NULL;
	GuiLabel* potion_four = NULL;
	GuiLabel* inventory = NULL;
	GuiLabel* stats = NULL;
	GuiLabel* map = NULL;
	GuiLabel* skill_tree = NULL;
	GuiLabel* game_menu = NULL;
	GuiLabel* run = NULL;

	GuiImage* primary_skill_image = NULL;
	GuiImage* secondary_skill_image = NULL;
	GuiImage* potion_image = NULL;
	GuiImage* potion_two_image = NULL;
	GuiImage* potion_three_image = NULL;
	GuiImage* potion_four_image = NULL;
	GuiImage* inventory_image = NULL;
	GuiImage* stats_image = NULL;
	GuiImage* map_image = NULL;
	GuiImage* skill_tree_image = NULL;
	GuiImage* game_menu_image = NULL;
	GuiImage* run_image = NULL;

	GuiButton* close_controls = NULL;
	//NOTE : added this list to iterate easily the gui_elements of the scene. Ask ric about a more optimal way to control the UI
	//NOTE: do the button class so it can have the diferent images and even a label, so it doesn?t interfere with the rest of the ui
	list<GuiElement*> intro_gui;

public:
	GuiLabel* controls_feedback = NULL;
};

#endif // __SNINTRO_H__

