#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"


#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

//NOTE4 : maybe the Ui would be more functional if applied with a set with branches for each scene, ask Ric

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
	focus = NULL;
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	GuiElement* hover_element = FindSelectedElement();

	if (hover_element && hover_element->focusable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		focus = hover_element;

	list<GuiElement*>::iterator item;
	
	//NOTE6 : here the modifications to STL can cause problems, if so, ask Ric, Maybe doing adapted functions to the stl system...
	//or maybe a Set/Map is a better solution
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{ 
		int index = 0;
		
		//Substitute for the p2List.Find() function
		for (item = gui_elements.begin(); item != gui_elements.end(); item++, index++)
		{
			if (*item == focus)
				break;
		}
		if (item == gui_elements.end())
			index = -1;
		//

		if (focus)
		{
			focus = NULL;
			index++;
			
			//Substitute for p2List.At() function
			item = gui_elements.begin();
			for (int i = 0; i < index && item != gui_elements.end(); i++, item++)
			{}
			//
			
		
			for (; item != gui_elements.end(); item++)
				if ((*item)->focusable)
				{
					focus = *item;
					break;
				}
		}

		if (!focus)
			for (item = gui_elements.begin(); item != gui_elements.end(); item++)
				if ((*item)->focusable)
				{
					focus = *item;
					break;
				}
	}

	for (item = gui_elements.begin(); item != gui_elements.end(); item++)
		if ((*item)->interactable)
			(*item)->CheckEvent(hover_element, focus);

	for (item = gui_elements.begin(); item != gui_elements.end(); item++)
			(*item)->Update(hover_element, focus);
	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{

	list<GuiElement*>::iterator item = gui_elements.begin();
	for (; item != gui_elements.end(); item++)
	{
		(*item)->Draw();
		if (App->debug)
			(*item)->DrawDebug();
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	list<GuiElement*>::iterator item = gui_elements.begin();
	for (; item != gui_elements.end(); item++)
		RELEASE((*item));

	gui_elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}


//Creators
GuiImage* j1Gui::AddGuiImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list)
{
	GuiImage* image = new GuiImage(p, r,par, list);
	gui_elements.push_back(image);
	return image;
}


GuiLabel* j1Gui::AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list)
{
	GuiLabel* label;

	if (f)
		label = new GuiLabel(t, f, p, par, list);
	else
		label = new GuiLabel(t, App->font->default, p, par, list);

	gui_elements.push_back(label);
	
	return label;
}

GuiInputBox* j1Gui::AddGuiInputBox(p2SString t ,_TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
{
	GuiInputBox* input = new GuiInputBox(t, f, p, width, r, offset, par, list);
	gui_elements.push_back(input);
	return input;
}

GuiElement* j1Gui::FindSelectedElement()
{	
	list<GuiElement*>::iterator item = gui_elements.end();

	for (; item != gui_elements.end(); item++)
	{
		if ((*item)->CheckCollision(App->input->GetMousePosition()))
		{
			return *item;
		}
	}
	return NULL;
}

//EXERCISE 1
GuiSlider* j1Gui::AddGuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list)
{
	GuiSlider* slider = new GuiSlider(p, tex_1, tex_2, width, thumb_h, offset, value, par, list);
	gui_elements.push_back(slider);
	return slider;
}
// class Gui ---------------------------------------------------*/

