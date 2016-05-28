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
#include "j1HUD.h"
#include "hudMiniMap.h"
#include "snOutdoor2.h"
#include "Item.h"


// Constructor
snDungeon2::snDungeon2() :j1Scene(DUNGEON_2)
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
	
	if (minimap_tex == NULL)
	{
		minimap_tex = App->game->HUD->minimap->minimap->image.outside_tex = App->tex->Load("maps/MiniMapdungeonMap2.png");
	}
	App->game->HUD->minimap->minimap->SetAlpha(App->game->HUD->minimap->minimap->image.outside_tex,90);


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
	if (App->new_game)
	{
		SpawnPlayer();
	}

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
			if (portal && App->sm->GetCurrentScene() == App->sm->level1)
			{
				portal->destiny = App->sm->level2;
			}
			else if (portal && App->sm->GetCurrentScene() == App->sm->level2)
			{
				portal->destiny = App->sm->level1;
			}

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
			//App->game->em->AddEnemy(p, ENEMY_CRAWLER, 1);
			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;
		}

		else if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && App->debug)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_WOLF, 1);

		}

		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && App->debug)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_CRAWLER, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && App->debug)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_COUNCIL, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && App->debug)
		{
			iPoint p;
			p = App->input->GetMouseWorldPosition();
			p.x += App->map->data.tile_width / 2;
			p.y += App->map->data.tile_height / 2;

			Entity* ent = App->game->em->AddEnemy(p, ENEMY_SHAMAN, 1);
		}

		else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN && App->debug)
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
Entity* snDungeon2::AddEnemy(iPoint pos)
{
	int lvl;
	Entity* ret = NULL;
	if (App->sm->level1 == App->sm->dungeon2)
	{
		lvl = 1;
		int random = rand() % 12;

		if (random <= 2)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER, lvl);
		}
		else if (random <= 5)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF, lvl);
		}
		else if (random <= 7)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_COUNCIL, lvl);
		}
		else if (random <= 9)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SUMMONER, lvl);
		}
		else if (random <= 11)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SHAMAN, lvl);
		}
	}

	else if (App->sm->level2 == App->sm->dungeon2)
	{
		lvl = 2;
		int random = rand() % 12;

		if (random <= 2)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_CRAWLER, lvl);
		}
		else if (random <= 5)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_WOLF, lvl);
		}
		else if (random <= 7)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_COUNCIL, lvl);
		}
		else if (random <= 9)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SUMMONER, lvl);
		}
		else if (random <= 11)
		{
			ret = App->game->em->AddEnemy(App->map->MapToWorld(pos.x, pos.y), ENEMY_SHAMAN, lvl);
		}
	}

	else if (App->sm->level3 == App->sm->dungeon2)
	{
		lvl = 3;

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
	}

	return ret;
}

Entity* snDungeon2::AddBoss(iPoint pos)
{
	int lvl;
	if (App->sm->level1 == App->sm->dungeon2)
	{
		lvl = 1;
	}

	else if (App->sm->level2 == App->sm->dungeon2)
	{
		lvl = 2;
	}

	else if (App->sm->level3 == App->sm->dungeon2)
	{
		lvl = 3;
	}
	Entity* ret = NULL;
	int random = rand() % 3;
	if (random == 0)
		ret = App->game->em->AddEnemy(pos, ENEMY_ANDARIEL, lvl);
	if (random == 1)
		ret = App->game->em->AddEnemy(pos, ENEMY_IZUAL, lvl);
	if (random == 2)
		ret = App->game->em->AddEnemy(pos, ENEMY_NEST, lvl);

	portal_spawn = pos;

	return ret;
}

void snDungeon2::AddPortal(iPoint pos)
{
	Entity* to_add = App->game->em->Add(portal_spawn, PORTAL);

	iPoint pos2;

	if (to_add == NULL)
	{
		pos2.x = portal_spawn.x;
		pos2.y = portal_spawn.y + 30;
		to_add = App->game->em->Add(pos2, PORTAL);
	}

	else if (to_add == NULL)
	{
		pos2.x = portal_spawn.x + 30;
		pos2.y = portal_spawn.y + 30;
		to_add = App->game->em->Add(pos2, PORTAL);
	}

	else if (to_add == NULL)
	{
		pos2.x = portal_spawn.x - 30;
		pos2.y = portal_spawn.y + 30;
		to_add = App->game->em->Add(pos2, PORTAL);
	}

	EntPortal* portal = (EntPortal*)to_add;
	if (portal != NULL)
	{
		if (App->sm->level1 == App->sm->dungeon2)
		{
			portal->SetDestiny(App->sm->level2);
		}

		else if (App->sm->level2 == App->sm->dungeon2)
		{
			//portal->destiny = App->sm->level3;
			portal->destiny = App->sm->win;
		}

		else if (App->sm->level3 == App->sm->dungeon2)
		{
			portal->destiny = App->sm->win;
		}
		entity_list.push_back(to_add);
	}
}

void snDungeon2::DropItem(iPoint pos)
{

	//NOTE: thinking of using srand for more equally distributed random generation
	//NOTE: have to change this, the random isn't equal at all. Even when there's a 60% to have no item, it almost always drops items
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (App->sm->level1 == App->sm->dungeon2)
	{
		rarity = RARITY_RARE;
	}

	else if (App->sm->level2 == App->sm->dungeon2)
	{
		rarity = RARITY_LEGENDARY;
	}

	if (rarity != NO_DROP)
	{
		chance = rand() % 100;

		if (chance < 35)
		{
			itmStone* item;
			item = new itmStone(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
			else
			{
				entity_list.push_back((Entity*)item->ent_item);
			}
		}
		else if (chance < 55)
		{
			itmRing* item;
			item = new itmRing(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
			else
			{
				entity_list.push_back((Entity*)item->ent_item);
			}
		}
		else if (chance < 65)
		{
			itmJewel* item;
			item = new itmJewel(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
			else
			{
				entity_list.push_back((Entity*)item->ent_item);
			}
		}
		else if (chance < 90)
		{
			itmRune* item;
			item = new itmRune(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
			else
			{
				entity_list.push_back((Entity*)item->ent_item);
			}
		}
		else if (chance >= 90)
		{
			itmArmor* item;
			item = new itmArmor(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
			else
			{
				entity_list.push_back((Entity*)item->ent_item);
			}
		}
	}
	else if (chance >= 65)
	{
		itmConsumable* item;
		item = new itmConsumable(rarity, pos);
		if (!item->ent_item)
		{
			RELEASE(item);
		}
		else
		{
			entity_list.push_back((Entity*)item->ent_item);
		}
	}
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
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 1)
	{
		pos = { 120, 2169 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 2)
	{
		pos = { -1262, 3101 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}	
	else if (random2 == 3)
	{
		pos = { -2340, 1961 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	
	//Add Enemies 1
	if (random != 0 && random2 != 0)
	{
		pos = { 109, 40 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
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
				to_add = AddEnemy(pos);
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
				to_add = AddEnemy(pos);
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
				to_add = AddEnemy(pos);
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
			to_add = AddEnemy(pos);
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
			to_add = AddEnemy(pos);
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
			to_add = AddEnemy(pos);
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
			to_add = AddEnemy(pos);
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
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 61, 142 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	pos = { 185, 70 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 4;
	}

	//X lines
	pos = { 87, 177 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 191, 125 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 144, 33 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	//Add Enemies 4
	pos = { 77, 121 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 79, 124 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 95, 155 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 97, 158 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 142, 155 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 144, 158 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 166, 141 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 168, 144 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 153, 105 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 155, 108 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 178, 105 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 180, 108 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 150, 73 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 152, 76 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 68, 57 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 70, 60 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 89, 35 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 91, 38 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	//Items
	DropItem({ 380, 3118 });
	DropItem({ 1402, 2270 });
	DropItem({ 61, 1265 });
	DropItem({ -2182, 2524 });
	DropItem({ -701, 2083 });
	DropItem({ -1379, 2543 });

}