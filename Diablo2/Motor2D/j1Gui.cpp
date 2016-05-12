#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Audio.h"
#include "Item.h"


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
	mouse_clicked == false;
	atlas = App->tex->Load(atlas_file_name.GetString());
	//Disables the cursor
	SDL_ShowCursor(SDL_DISABLE);
	//Mouse--------
	mouse = new GuiMouseImage({ mouse_x, mouse_y }, { 189, 98, 33, 26 }, NULL, this);
	dragged_item = NULL;
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

	if (dragged_item)
	{
		dragged_item->Move();
		if (hover_element == NULL && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			//dragged_item->inventory->items.remove(dragged_item);
			//RELEASE(dragged_item);
			dragged_item->nexus->ConvertToEntity(App->input->GetMouseWorldPosition());
			dragged_item = NULL;
			mouse_hovering = true;
		}
	}

	
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
	

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		mouse_clicked = true;
		mouse->SetTextureRect({ 222, 98, 33, 26 });
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		mouse_clicked = true;
		mouse->SetTextureRect({ 222, 98, 33, 26 });
	}
	else if (mouse_clicked == true)
	{
		mouse_clicked = false;
		mouse->SetTextureRect({ 189, 98, 33, 26 });
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

	if (dragged_item)
	{
		dragged_item->Draw();
		if (App->debug)
		{
			dragged_item->DrawDebug();
		}
	}
	//
	else
	{
		mouse->Draw();
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	/*
	NOTE: Commenting this because crash

	list<GuiElement*>::iterator item = gui_elements.begin();
	for (; item != gui_elements.end(); item++)
		RELEASE(*item);

	gui_elements.clear();
	*/

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
	if (image->parent != NULL)image->parent->AddChild(image);
	gui_elements.push_back(image);
	return image;
}

GuiLabel* j1Gui::AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, SDL_Color color ,SDL_Color background, j1Module* list)
{
	GuiLabel* label;
	
	if (f)
		label = new GuiLabel(t, f, p, color, par, list, background);
	else
		label = new GuiLabel(t, App->font->default, p, color, par, list, background);

	gui_elements.push_back(label);
	if (label->parent != NULL)label->parent->AddChild(label);
	return label;
}
GuiLabel* j1Gui::AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, SDL_Color color, j1Module* list)
{
	GuiLabel* label;
	if (f)
		label = new GuiLabel(t, f, p, color, par, list);
	else
		label = new GuiLabel(t, App->font->default, p, color, par, list);

	gui_elements.push_back(label);
	if (label->parent != NULL)label->parent->AddChild(label);
	return label;
}
GuiLabel* j1Gui::AddGuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list)
{
	GuiLabel* label;
	SDL_Color color = FONT_BLACK;
	if (f)
		label = new GuiLabel(t, f, p, color, par, list);
	else
		label = new GuiLabel(t, App->font->default, p, color, par, list);

	gui_elements.push_back(label);
	if (label->parent != NULL)label->parent->AddChild(label);
	return label;
}
GuiImage* j1Gui::AddGuiImageWithLabel(iPoint p, SDL_Rect r, p2SString t, _TTF_Font* f, iPoint i, GuiElement* par, j1Module* list)
{
	SDL_Color backgroundColor = { 0, 0, 0, 50 };
	GuiImage* image = new GuiImage(p, r, par, list);
	if (image->parent != NULL)image->parent->AddChild(image);
	gui_elements.push_back(image);
	i.x = i.x + image->GetScreenPosition().x;
	i.y = i.y + image->GetScreenPosition().y - r.h;
	GuiLabel* label = AddGuiLabel(t, f, i, NULL, FONT_WHITE, backgroundColor, list);
	
	image->SetLabel(label);
	gui_elements.push_back(label);
	return image;
}

GuiInputBox* j1Gui::AddGuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
{
	GuiInputBox* input = new GuiInputBox(t, f, p, width, r, offset, par, list);
	gui_elements.push_back(input);
	if (input->parent != NULL)input->parent->AddChild(input);
	return input;
}

GuiButton* j1Gui::AddGuiButton(iPoint p, SDL_Rect idle_r1, SDL_Rect hover_r1, SDL_Rect click_r1, p2SString t, _TTF_Font* f , j1Module* list, GuiElement* parent)
{
	GuiButton* button = new GuiButton(p, idle_r1, hover_r1, click_r1, t, f, list, parent);
	gui_elements.push_back(button);
	if (button->parent != NULL)button->parent->AddChild(button);
	return button;

}
GuiText* j1Gui::AddGuiText(iPoint p, vector<StringColor> text, GuiElement* par, j1Module* list)
{
	GuiText* Text = new GuiText(p, text, par, list);
	gui_elements.push_back(Text);
	if (Text->parent != NULL)Text->parent->AddChild(Text);
	return Text;
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
GuiAnimation* j1Gui::AddGuiAnimation(iPoint p, Animation anima, SDL_Texture* texture, GuiElement* par, j1Module* list)
{
	GuiAnimation* anim = new GuiAnimation(p,anima,texture, par,  list);
	gui_elements.push_back(anim);
	if (par != NULL)par->AddChild(anim);
	return anim;
}


//EXERCISE 1
GuiSlider* j1Gui::AddGuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list)
{
	GuiSlider* slider = new GuiSlider(p, tex_1, tex_2, width, thumb_h, offset, value, par, list);
	gui_elements.push_back(slider);
	if (par != NULL)par->AddChild(slider);
	return slider;
}


GuiInventory* j1Gui::AddGuiInventory(iPoint p, SDL_Rect r, int col, int rows, int slot_w, int slot_h, GuiElement* par, j1Module* list)
{
	GuiInventory* inventory = new GuiInventory(p, r, col, rows, slot_w, slot_h, par, list);
	gui_elements.push_back(inventory);

	if (par != NULL)par->AddChild(inventory);
	return inventory;
}


GuiSkill* j1Gui::AddGuiSkill(iPoint p, SDL_Rect r, SDL_Rect r2, Skill* s, GuiElement* par, j1Module* list)
{
	GuiSkill* skill = new GuiSkill(p, r, r2, s, par, list);
	gui_elements.push_back(skill);

	if (par != NULL)par->AddChild(skill);
	return skill;
}

GuiMiniMap* j1Gui::AddGuiMiniMap(iPoint p, SDL_Rect r, SDL_Texture* tex, GuiElement* par, j1Module* list)
{
	
	GuiMiniMap* minimap = new GuiMiniMap(p, r,tex, par, list);
	gui_elements.push_back(minimap);

	if (par != NULL)par->AddChild(minimap);

	return minimap;
}
// class Gui ---------------------------------------------------*/