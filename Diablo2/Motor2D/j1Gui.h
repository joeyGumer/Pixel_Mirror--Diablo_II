#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
//I'm doing trap here...
//So i can take this out i have to change the constructors..., i'll do it later
#include "GuiElements.h"


#define CURSOR_WIDTH 2

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	
	
	// Gui creation functions
	GuiImage* AddGuiImage(iPoint p, SDL_Rect r, GuiElement* par,j1Module* list);
	GuiLabel* AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list);
	GuiInputBox* AddGuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list);

	//EXERCISE 1
	GuiSlider* AddGuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list);

	//Get selected element
	GuiElement* FindSelectedElement();

	SDL_Texture* GetAtlas() const;


	p2List<GuiElement*> gui_elements;
private:
	bool         debug;
	SDL_Texture* atlas;
	p2SString atlas_file_name;

	GuiElement* focus;

};

#endif // __j1GUI_H__