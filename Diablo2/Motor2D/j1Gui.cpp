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

	debug = false;

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	//Disables the cursor
	SDL_ShowCursor(SDL_DISABLE);
	//Mouse--------
	mouse = new GuiMouseImage({ mouse_x, mouse_y }, { 189, 97, 34, 28 }, NULL, this);
	//-------------
	return true;
}

//NOTE: puted the active boolean in action,not only a function because when activated again it needs to have the same stats as before
// Update all guis
bool j1Gui::PreUpdate()
{
	//Interaction with mouse reseted every beginning of iteration
	mouse_hovering = false;

	//Updating the mouse cursor image
	mouse->Update();
	//---------------
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	GuiElement* hover_element = FindSelectedElement();

	if (hover_element && hover_element->focusable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		focus = hover_element;

	list<GuiElement*>::iterator item;

	//NOTE: for now, we don't need the focus
	/*if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		//int index = gui_elements.find(focus);
		//substitute for focus
		item = gui_elements.begin();
		int index = 0;
		while (item != gui_elements.end())
		{
			if ((*item) == focus)
				break;

			index++;
			item++;
		}
		if (item == gui_elements.end())
			index = -1;
		//
		if (focus)
		{
			focus = NULL;
			index++;
			item = gui_elements.begin();
			//substitute for "at"
			for (int pos = 0; item != gui_elements.end(); item++)
			{
				if (pos == index)
					break;

				pos++;
			}

			for (; item != gui_elements.end(); item++)
			{
				if ((*item)->focusable)
				{
					focus = *item;
					break;
				}
			}
		}

		if (!focus)
			for (item = gui_elements.begin(); item != gui_elements.end(); item++)
			{
				if ((*item)->focusable)
				{
					focus = *item;
					break;
				}
			}
	}*/

	//NOTE, if we use the changeScene at OnEvent, it crashes here , even if there are no items, it says that there's an item without content (NULL)
	//Ask ric with more questions about UI
	for (item = gui_elements.begin(); item != gui_elements.end(); item++)
	{
		//Checks the interactable items and the hover one, to check if there's any mouse interaction (because the player doen't move when interacting with GUI)
		if (((*item)->interactable || (*item) == hover_element) && (*item)->active)
		{
			(*item)->CheckEvent(hover_element, focus, mouse_hovering);
			
		}
	}

	for (item = gui_elements.begin(); item != gui_elements.end(); item++)
	{
		if ((*item)->active)
			(*item)->Update(hover_element, focus);
	}

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	//Mouse----------
	

	list<GuiElement*>::iterator item = gui_elements.begin();
	for (; item != gui_elements.end(); item++)
	{
		if ((*item)->active)
		{
			if ((*item)->debug == false)
			{
				(*item)->Draw();
				if (App->debug)
					(*item)->DrawDebug();
			}
			else
			{
				if (App->debug)
					(*item)->Draw();
			}
		}
	}

	mouse->Draw();

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	list<GuiElement*>::iterator item = gui_elements.begin();
	for (; item != gui_elements.end(); item++)
		RELEASE(*item);

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
	GuiImage* image = new GuiImage(p, r, par, list);
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

GuiInputBox* j1Gui::AddGuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
{
	GuiInputBox* input = new GuiInputBox(t, f, p, width, r, offset, par, list);
	gui_elements.push_back(input);
	return input;
}

GuiButton* j1Gui::AddGuiButton(iPoint p, SDL_Rect idle_r1, SDL_Rect hover_r1, SDL_Rect click_r1, p2SString t, _TTF_Font* f , j1Module* list, GuiElement* parent)
{
	GuiButton* button = new GuiButton(p, idle_r1, hover_r1, click_r1, t, f, list, parent);
	gui_elements.push_back(button);
	return button;

}

GuiElement* j1Gui::FindSelectedElement()
{
	list<GuiElement*>::reverse_iterator item = gui_elements.rbegin();

	for (; item != gui_elements.rend(); item++)
	{
		if ((*item)->CheckCollision(App->input->GetMousePosition()) && (*item)->active)
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