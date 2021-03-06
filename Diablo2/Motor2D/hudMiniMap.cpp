#include "hudMiniMap.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "GuiMiniMap.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1SceneManager.h"
#include "snDungeon2.h"

#include "j1HUD.h"
#include "guiMiniMap.h"




//Constructor
//Don't now why the code makes me put semicolons everywhere
;
hudMiniMap::hudMiniMap() : hudElement()
{
	name.create("hud_minimap");
}

//Destructor
hudMiniMap::~hudMiniMap()
{

}

//Called before fist frame
bool hudMiniMap::Start()
{
	active = false;
 
	SDL_Texture* mapa = App->tex->Load("maps/MiniMapdungeonMap2.png");
	//SDL_Texture* mapa = NULL;
	//Creation of the minimap
	minimap = App->gui->AddGuiMiniMap({ 100, 20 }, { 0, 0, 400, 200 }, mapa, NULL, this);
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
