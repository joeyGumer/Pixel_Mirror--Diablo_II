#include "snDungeon1.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Pathfinding.h"
#include "j1Game.h"
#include "j1EntityManager.h"
#include "Entity.h"
#include "j1Input.h"




// Constructor
snDungeon1::snDungeon1()
{

}

// Destructor
snDungeon1::~snDungeon1()
{

}

// Called before render is available
bool snDungeon1::Awake(pugi::xml_node& conf)
{
	return true;
}


// Called the first frame
bool snDungeon1::Start()
{

	debug = App->tex->Load("maps/mini_path.png");

	//Map
	/*if (App->map->Load("map_dungeon.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}*/

	return true;
}


// PreUpdate
bool snDungeon1::PreUpdate()
{
	return true;
}


// Update
bool snDungeon1::Update(float dt)
{
	//Map
	App->map->Draw();

	//Entities for debug
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		iPoint p;
		p = App->input->GetMouseWorldPosition();
		p.x += App->map->data.tile_width / 2;
		p.y += App->map->data.tile_height / 2;

		//int a = rand() % 2;
		//if (a == 0)
		App->game->em->Add(p, ENEMY);
	}

	return true;
}


// PostUpdate
bool snDungeon1::PostUpdate()
{
	return true;
}


// Called before quitting
bool snDungeon1::CleanUp()
{
	// Remove all entities
	list<Entity*>::iterator item;
	item = entity_list.begin();

	while (item != entity_list.end())
	{
		App->game->em->Remove((*item)->id);
		item++;
	}
	entity_list.clear();
	return true;
}


// Called on certain event
void snDungeon1::OnEvent(GuiElement* element, GUI_Event even)
{

}


//Load/UnLoad, called when the scene changes
bool snDungeon1::Load()
{
	Start();
	return true;
}

bool snDungeon1::UnLoad()
{
	CleanUp();
	return true;
}
