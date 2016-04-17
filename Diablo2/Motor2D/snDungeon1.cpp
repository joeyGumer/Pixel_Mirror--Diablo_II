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
	if (App->map->Load("map_dungeon.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	AddEnemies();

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
		//App->game->em->Add(p, ENEMY);
		//App->game->em->Add(p, ENEMY_CRAWLER);
		App->game->em->Add(p, ENEMY_CRAWLER);
		p = App->map->WorldToMap(p.x, p.y);
		int i = 0;
	}


	if (App->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			App->render->camera.x -= floor(CAM_SPEED * 5 * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			App->render->camera.x += floor(CAM_SPEED * 5 * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			App->render->camera.y -= floor(CAM_SPEED * 5 * dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			App->render->camera.y += floor(CAM_SPEED * 5 * dt);
		}
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
		App->game->em->Remove(item._Ptr->_Myval->id);
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

//Adding Enemies
void snDungeon1::AddEnemies()
{
	iPoint tile_pos = { 20, 141 };
	Entity* to_add = NULL;
	/*
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 20, 141 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 25, 141 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 22, 147 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 27, 147 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 25, 152 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 22, 152 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 18, 122 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 22, 122 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 20, 130 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 24, 130 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));

	tile_pos = { 18, 73 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 22, 73 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 17, 77 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 20, 77 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 14, 82 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 22, 82 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 18, 87 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 20, 87 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));


	tile_pos = { 149, 25 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 150, 28 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 155, 30 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 156, 32 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 162, 35 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 164, 33 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 159, 25 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 150, 34 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 145, 30 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 146, 32 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 152, 35 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 154, 33 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));

	tile_pos = { 76, 25 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 78, 28 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 80, 30 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 82, 32 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 72, 25 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 72, 23 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));

	tile_pos = { 62, 93 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 65, 88 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 60, 93 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 68, 89 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 72, 90 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	tile_pos = { 72, 92 };
	entity_list.push_back(App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER));
	*/

	tile_pos = { 182, 80 };
	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x -= 4;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 4;
	}

	tile_pos = { 159, 92 };
	for (int i = 0; i < 6; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 4;
	}

	tile_pos = { 105, 82 };
	for (int i = 0; i < 6; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 3;
	}

	tile_pos = { 204, 47 };
	for (int i = 0; i < 7; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 2;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 3;
	}

	tile_pos = { 52, 108 };
	for (int i = 0; i < 4; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 4;
	}

	tile_pos = { 131,	35 };
	for (int i = 0; i < 13; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 1;
		}
		to_add = App->game->em->Add(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 2;
	}
}
