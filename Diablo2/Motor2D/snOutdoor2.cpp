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

			EntPortal* portal = (EntPortal*)App->game->em->Add(p, PORTAL);
			if (portal)
				portal->destiny = App->sm->outdoor1;

			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;
		}

		else if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_WOLF, 1);
			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;

		}

		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_CRAWLER, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_COUNCIL, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_SHAMAN, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_SUMMONER, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_IZUAL, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_ANDARIEL, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_NEST, 1);
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
Entity* snOutdoor2::AddEnemy(iPoint pos)
{
	int lvl;
	if (App->sm->level1 == App->sm->outdoor2)
	{
		lvl = 1;
	}

	else if (App->sm->level2 == App->sm->outdoor2)
	{
		lvl = 2;
	}

	else if (App->sm->level3 == App->sm->outdoor2)
	{
		lvl = 3;
	}
	Entity* ret = NULL;
	int random = rand() % 5;
	if (random == 0)
		ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER, lvl);
	if (random == 1)
		ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF, lvl);
	if (random == 2)
		ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_COUNCIL, lvl);
	if (random == 3)
		ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SUMMONER, lvl);
	if (random == 4)
		ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SHAMAN, lvl);

	return ret;
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
		to_add = App->game->em->AddEnemy(pos, ENEMY_IZUAL, 1);
		entity_list.push_back(to_add);
	}
	else if (random2 == 1)
	{
		pos = { -3041, 2106 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_IZUAL, 1);
		entity_list.push_back(to_add);
	}
	else if (random2 == 2)
	{
		pos = { -224, 4200 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_IZUAL, 1);
		entity_list.push_back(to_add);
	}
	else if (random2 == 3)
	{
		pos = { 2815, 2839 };
		to_add = App->game->em->AddEnemy(pos, ENEMY_IZUAL, 1);
		entity_list.push_back(to_add);
	}

	//Add Enemies 1
	if (random != 0 && random2 != 0)
	{
		pos = { 34, 42 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 42;
		}
	}
	if (random != 1 && random2 != 1)
	{
		pos = { 28, 181 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 181;
		}
	}

	if (random != 2 && random2 != 2)
	{
		pos = { 202, 213 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 213;
		}
	}
	if (random != 3 && random2 != 3)
	{
		pos = { 209, 69 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 69;
		}
	}

	//Add Enemies 2
	pos = { 93, 176 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 176;
	}

	pos = { 166, 190 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 190;
	}

	pos = { 204, 94 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 94;
	}

	pos = { 137, 65 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 65;
	}

	pos = { 46, 74 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 74;
	}

	pos = { 39, 114 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 114;
	}

	//Add Enemies 3
	//Y lines
	pos = { 73, 89 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 147, 109 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 64, 158 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	//X lines
	pos = { 163, 209 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 156, 39 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 73, 41 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	
	//Add Enemies 4
	pos = { 91, 55 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 93, 58 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 99, 130 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 101, 133 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 62, 199 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 64, 202 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 191, 128 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 193, 131 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 208, 166 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 210, 169 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 167, 156 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 169, 159 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 200, 36 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 202, 39 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
}
