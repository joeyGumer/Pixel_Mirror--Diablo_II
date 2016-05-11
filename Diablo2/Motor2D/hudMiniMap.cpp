#include "hudMiniMap.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "GuiMiniMap.h"




//Constructor
//Don't now why the code makes me put semicolons everywhere
;
hudMiniMap::hudMiniMap() : hudElement()
{

}

//Destructor
hudMiniMap::~hudMiniMap()
{

}

//Called before fist frame
bool hudMiniMap::Start()
{
	active = false;

	background = App->gui->AddGuiImage({ 150, 0 }, { 1128, 588, 300, 100 }, NULL, this);
	background->active = false;
	hud_gui_elements.push_back(background);

	//Creation of the minimap
	minimap = App->gui->AddGuiMiniMap({ 16, 100 }, { 1144, 843, 290, 87 }, background, this);
	minimap->active = false;
	hud_gui_elements.push_back(minimap);

	



	return true;
}

//Called before each loop iteration
bool hudMiniMap::PreUpdate()
{
	
	return true;
}

//Called each frame
bool hudMiniMap::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudMiniMap::PostUpdate()
{
	return true;
}

//Called before quitting
bool hudMiniMap::CleanUp()
{
	/*
	//WARNING: can't do this plox
	App->gui->dragged_item = NULL;
	if (inventory)
		inventory->CleanItems();

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == hud_gui_elements[i])
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	hud_gui_elements.clear();
	inventory = NULL;
	*/

	return true;
}

void hudMiniMap::Activate()
{
	active = !active;

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->active = active;
	}


}



//Called when there's a gui event
void hudMiniMap::OnEvent(GuiElement* element, GUI_Event even)
{

}
