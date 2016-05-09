#include "snDungeon2.h"
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
snDungeon2::snDungeon2()
{

}

// Destructor
snDungeon2::~snDungeon2()
{

}

// Called before render is available
bool snDungeon2::Awake(pugi::xml_node& conf)
{
	return true;
}


// Called the first frame
bool snDungeon2::Start()
{
	win = false;

	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	if (debug == NULL)
		debug = App->tex->Load("maps/mini_path.png");

	//Map
	if (App->map->Load("map_dungeon2.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	//Spawns
	SpawnPlayer();

	AddEnemies();

	return true;
}


// PreUpdate
bool snDungeon2::PreUpdate()
{
	return true;
}


// Update
bool snDungeon2::Update(float dt)
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
bool snDungeon2::PostUpdate()
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
bool snDungeon2::CleanUp()
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
void snDungeon2::OnEvent(GuiElement* element, GUI_Event even)
{

}


//Load/UnLoad, called when the scene changes
bool snDungeon2::Load()
{
	Start();
	return true;
}

bool snDungeon2::UnLoad()
{
	CleanUp();
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	return true;
}

//Adding Enemies
void snDungeon2::AddEnemies()
{
	
}

//Spawn Player
void snDungeon2::SpawnPlayer()
{
	//Add Player
	int random = rand() % 4;
	if (random == 0)
		App->game->player->SetPosition({ 1442, 1530 });
	else if (random == 1)
		App->game->player->SetPosition({ 120, 2169 });
	else if (random == 2)
		App->game->player->SetPosition({ -1262, 3101 });
	else if (random == 3)
		App->game->player->SetPosition({ -2340, 1961 });

	//Add Boss
	int random2 = rand() % 4;
	while (random2 == random)
	{
		random2 = rand() % 4;
	}
	Entity* to_add = NULL;
	iPoint pos;
	if (random2 == 0)
	{
		pos = { 1442, 1530 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 1)
	{
		pos = { 120, 2169 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 2)
	{
		pos = { -1262, 3101 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 3)
	{
		pos = { -2340, 1961 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}
		
}