#include "snOutdoor2.h"
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
snOutdoor2::snOutdoor2()
{

}

// Destructor
snOutdoor2::~snOutdoor2()
{

}

// Called before render is available
bool snOutdoor2::Awake(pugi::xml_node& conf)
{
	return true;
}


// Called the first frame
bool snOutdoor2::Start()
{
	win = false;

	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	if (debug == NULL)
		debug = App->tex->Load("maps/mini_path.png");

	//Map
	if (App->map->Load("map_outdoor2.tmx") == true)
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
bool snOutdoor2::PreUpdate()
{
	return true;
}


// Update
bool snOutdoor2::Update(float dt)
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
bool snOutdoor2::PostUpdate()
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
bool snOutdoor2::CleanUp()
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
void snOutdoor2::OnEvent(GuiElement* element, GUI_Event even)
{

}


//Load/UnLoad, called when the scene changes
bool snOutdoor2::Load()
{
	Start();
	return true;
}

bool snOutdoor2::UnLoad()
{
	CleanUp();
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	return true;
}

//Adding Enemies
void snOutdoor2::AddEnemies()
{

}

//Spawn Player
void snOutdoor2::SpawnPlayer()
{
	//Add Player
	int random = rand() % 4;
	if (random == 0)
		App->game->player->SetPosition({ -140, 796 });
	else if (random == 1)
		App->game->player->SetPosition({ -3041, 2106 });
	else if (random == 2)
		App->game->player->SetPosition({ -224, 4200 });
	else if (random == 3)
		App->game->player->SetPosition({ 2815, 2839 });

	
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
		pos = { -140, 796 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}
	else if (random2 == 1)
	{
		pos = { -3041, 2106 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}
	else if (random2 == 2)
	{
		pos = { -224, 4200 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}
	else if (random2 == 3)
	{
		pos = { 2815, 2839 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_COUNCIL);
		entity_list.push_back(to_add);
	}

	/*
	//Add Enemies 1
	if (random != 0 && random2 != 0)
	{
		pos = { 109, 40 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 40;
		}
	}
	if (random != 1 && random2 != 1)
	{
		pos = { 105, 102 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 102;
		}
	}

	if (random != 2 && random2 != 2)
	{
		pos = { 120, 182 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 182;
		}
	}
	if (random != 3 && random2 != 3)
	{
		pos = { 35, 153 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 153;
		}
	}

	//Add Enemies 2
	pos = { 109, 123 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 123;
	}

	pos = { 117, 153 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 153;
	}

	pos = { 62, 182 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 182;
	}

	pos = { 178, 46 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 46;
	}

	//Add Enemies 3
	//Y lines
	pos = { 109, 67 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 61, 142 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 185, 70 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	//X lines
	pos = { 87, 177 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 191, 125 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 144, 33 };
	for (int i = 0; i < 3; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	//Add Enemies 4
	pos = { 77, 121 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 79, 124 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 95, 155 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 97, 158 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 142, 155 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 144, 158 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 166, 141 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 168, 144 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 153, 105 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 155, 108 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 178, 105 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 180, 108 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 150, 73 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 152, 76 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 68, 57 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 70, 60 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);

	pos = { 89, 35 };
	for (int i = 0; i < 2; i++)
	{
		to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 91, 38 };
	to_add = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF);
	entity_list.push_back(to_add);
	*/
}
