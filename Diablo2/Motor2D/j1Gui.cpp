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

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	GuiElement* hover_element = FindSelectedElement();

	if (hover_element && hover_element->focusable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		focus = hover_element;

	p2List_item<GuiElement*>* item;
	
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{ 
		int index = gui_elements.find(focus);
		if (focus)
		{
			focus = NULL;
			index++;
			item = gui_elements.At(index);
			for (; item; item = item->next)
				if (item->data->focusable)
				{
					focus = item->data;
					break;
				}
		}

		if (!focus)
			for (item = gui_elements.start; item; item = item->next)
				if (item->data->focusable)
				{
					focus = item->data;
					break;
				}
	}

	for (item = gui_elements.start; item; item = item->next)
		if (item->data->interactable)
			item->data->CheckEvent(hover_element, focus);

	for (item = gui_elements.start; item; item = item->next)
			item->data->Update(hover_element, focus);
	
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{

	p2List_item<GuiElement*>* item = gui_elements.start;
	for (; item; item = item->next)
	{
		item->data->Draw();
		if (debug)
			item->data->DrawDebug();
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<GuiElement*>* item = gui_elements.start;
	for (; item; item = item->next)
		RELEASE(item->data);

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
	gui_elements.add(image);
	return image;
}


GuiLabel* j1Gui::AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list)
{
	GuiLabel* label;

	if (f)
		label = new GuiLabel(t, f, p, par, list);
	else
		label = new GuiLabel(t, App->font->default, p, par, list);

	gui_elements.add(label);
	
	return label;
}

GuiInputBox* j1Gui::AddGuiInputBox(p2SString t ,_TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
{
	GuiInputBox* input = new GuiInputBox(t, f, p, width, r, offset, par, list);
	gui_elements.add(input);
	return input;
}

GuiElement* j1Gui::FindSelectedElement()
{	
	p2List_item<GuiElement*>* item = gui_elements.end;

	for (; item; item = item->prev)
	{
		if (item->data->CheckCollision(App->input->GetMousePosition()))
		{
			return item->data;
		}
	}
	return NULL;
}

//EXERCISE 1
GuiSlider* j1Gui::AddGuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list)
{
	GuiSlider* slider = new GuiSlider(p, tex_1, tex_2, width, thumb_h, offset, value, par, list);
	gui_elements.add(slider);
	return slider;
}
// class Gui ---------------------------------------------------*/

