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
#include "j1SceneManager.h"
#include "snWin.h"
#include "j1Audio.h"
#include "snOutdoor1.h"
#include "j1Player.h"
#include "EntPortal.h"
#include "EntEnemy.h"



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
	win = false;

	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	if (debug == NULL)
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

	App->game->player->SetPosition({0, 500});

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

	if (App->debug)
	{
		//Entities for debug
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && debug)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			//int a = rand() % 2;
			//if (a == 0)
			//App->game->em->Add(p, ENEMY);
			//App->game->em->Add(p, ENEMY_CRAWLER);
			EntPortal* portal = (EntPortal*)App->game->em->Add(p, PORTAL);
			if (portal)
				portal->destiny = App->sm->outdoor1;

			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;
		}

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
			App->game->em->AddEnemy(p, ENEMY_CRAWLER);
			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;
		}

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
	//NOTE: In progress
	if (App->game->player->TeleportReady())
	{
		j1Scene* destiny = App->game->player->GetDestiny();
		App->game->player->ResetTeleport();
		App->sm->ChangeScene(destiny);
	}

	if (win)
	{
		App->sm->ChangeScene(App->sm->win);
	}
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
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	return true;
}

//Adding Enemies
void snDungeon1::AddEnemies()
{
	iPoint tile_pos;
	Entity* to_add = NULL;

	tile_pos = { -140, 417 };
	to_add = App->game->em->Add(tile_pos, PORTAL);
	entity_list.push_back(to_add);
	EntPortal* portal = (EntPortal*)to_add;
	if (portal)
		portal->SetDestiny(portal->destiny = App->sm->outdoor1);

	tile_pos = { 182, 80 };
	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x -= 4;
		}
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
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
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
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
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
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
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
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
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
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
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		tile_pos.y -= 2;
	}

	tile_pos = { 127, 160 };
	for (int i = 0; i < 13; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 2;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
		
		tile_pos.y -= 3;
	}

	tile_pos = { 204, 141 };
	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 1;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
		tile_pos.y -= 2;
	}

	tile_pos = { 204, 222 };
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
			tile_pos.y -= 3;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
	}

	tile_pos = { 96, 222 };
	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
			tile_pos.y -= 3;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
	}

	tile_pos = { 100, 205 };
	for (int i = 0; i < 8; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
			tile_pos.y += 3;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
	}

	tile_pos = { 18, 94 };
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
		}

		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);
		
		tile_pos.y += 2;
	}

	tile_pos = { 19, 120 };
	for (int i = 0; i < 8; i++)
	{

		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);

		tile_pos.y += 2;
	}

	tile_pos = { 69, 22 };
	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
			tile_pos.y += 3;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
	}

	tile_pos = { 19, 216 };
	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 2;
			tile_pos.y += 2;
		}
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
		if (to_add != NULL)
			entity_list.push_back(to_add);

		tile_pos.x -= 1;
		tile_pos.y -= 3;
	}

	tile_pos = { 93, 138 };
	App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_COUNCIL);

	tile_pos = { 93, 149 };
	for (int i = 0; i < 6; i++)
	{
		if (i % 2 == 1)
		{
			tile_pos.x += 3;
			tile_pos.y -= 3;
		}
		else
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(tile_pos.x, tile_pos.y), ENEMY_CRAWLER);
			if (to_add != NULL)
				entity_list.push_back(to_add);
		}
	}
}
