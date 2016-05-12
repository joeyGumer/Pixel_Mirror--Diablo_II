#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
//I'm doing trap here...
//So i can take this out i have to change the constructors..., i'll do it later
#include "GuiElements.h"
#include "GuiInventory.h"
#include "GuiSkill.h"
#include "GuiMiniMap.h"
#include <vector>
#include <list>


#define CURSOR_WIDTH 2

// ---------------------------------------------------
;
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
	GuiImage* AddGuiImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list);
	GuiImage* AddGuiImageWithLabel(iPoint p, SDL_Rect r, p2SString t, _TTF_Font* f, iPoint i, GuiElement* par, j1Module* list);
	GuiLabel* AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, SDL_Color color, SDL_Color background, j1Module* list);
	GuiLabel* AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, SDL_Color color, j1Module* list);
	GuiLabel* AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list);
	GuiInputBox* AddGuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list);
	GuiButton* AddGuiButton(iPoint p, SDL_Rect idle_r1, SDL_Rect hover_r1, SDL_Rect click_r1, p2SString t = "", _TTF_Font* f = NULL, j1Module* list = NULL, GuiElement* parent = NULL);
	GuiSlider* AddGuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list);
	GuiSkill* AddGuiSkill(iPoint p, SDL_Rect r, SDL_Rect r2, Skill* s, GuiElement* par, j1Module* list);
	GuiMiniMap* AddGuiMiniMap(iPoint p, SDL_Rect r, SDL_Texture* tex, GuiElement* par, j1Module* list);
	GuiLabel* SetLabel();
	GuiMouseImage* AddGuiMouseImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list);
	GuiText* AddGuiText(iPoint p, vector<StringColor> text, GuiElement* par, j1Module* list = NULL);
	//Function that creates an inventory
	GuiInventory* AddGuiInventory(iPoint p, SDL_Rect r, int columns, int rows, int slot_w, int slot_h, GuiElement* par = NULL, j1Module* list = NULL);
	
	
	//Get selected element
	GuiElement* FindSelectedElement();

	
	SDL_Texture* GetAtlas() const;

public:

	list<GuiElement*> gui_elements;
	bool			mouse_hovering;
	GuiItem*		dragged_item;

private:
	bool			debug;
	bool            mouse_clicked;
	SDL_Texture*	atlas;
	p2SString		atlas_file_name;
	int             mouse_x, mouse_y;

	GuiElement*		focus;
	GuiMouseImage* mouse = NULL;
};

#endif // __j1GUI_H__