#include "snDungeon3.h"
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
snDungeon3::snDungeon3() :j1Scene(DUNGEON_3)
{

}

// Destructor
snDungeon3::~snDungeon3()
{

}

// Called before render is available
bool snDungeon3::Awake(pugi::xml_node& conf)
{
	return true;
}


// Called the first frame
bool snDungeon3::Start()
{
	win = false;

	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	if (minimap_tex == NULL)
	{
		App->game->HUD->minimap->minimap->image.outside_tex = App->tex->Load("maps/MiniMapdungeonMap3.png");
	}
	App->game->HUD->minimap->minimap->SetAlpha(App->game->HUD->minimap->minimap->image.outside_tex, 90);


	if (debug == NULL)
		debug = App->tex->Load("maps/mini_path.png");

	//Map
	if (App->map->Load("map_dungeon3.tmx") == true)
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
bool snDungeon3::PreUpdate()
{
	return true;
}


// Update
bool snDungeon3::Update(float dt)
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
bool snDungeon3::PostUpdate()
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
bool snDungeon3::CleanUp()
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
void snDungeon3::OnEvent(GuiElement* element, GUI_Event even)
{

}


//Load/UnLoad, called when the scene changes
bool snDungeon3::LoadScene()
{
	Start();
	return true;
}

bool snDungeon3::UnLoad()
{
	CleanUp();
	App->map->CleanUp();
	App->pathfinding->CleanUp();
	return true;
}

//Adding Enemies
Entity* snDungeon3::AddEnemy(iPoint pos)
{
	int lvl;
	Entity* ret = NULL;
	if (App->sm->level1 == App->sm->dungeon3)
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

	else if (App->sm->level2 == App->sm->dungeon3)
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

	else if (App->sm->level3 == App->sm->dungeon3)
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

Entity* snDungeon3::AddBoss(iPoint pos)
{
	int lvl = 1;
	if (App->sm->level1 == App->sm->dungeon3)
	{
		lvl = 1;
	}

	else if (App->sm->level2 == App->sm->dungeon3)
	{
		lvl = 2;
	}

	else if (App->sm->level3 == App->sm->dungeon3)
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

void snDungeon3::AddPortal(iPoint pos)
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
		if (App->sm->level1 == App->sm->dungeon3)
		{
			portal->SetDestiny(App->sm->level2);
		}

		else if (App->sm->level2 == App->sm->dungeon3)
		{
			//portal->destiny = App->sm->level3;
			portal->destiny = App->sm->win;
		}

		else if (App->sm->level3 == App->sm->dungeon3)
		{
			portal->destiny = App->sm->win;
		}
		entity_list.push_back(to_add);
	}
}

void snDungeon3::DropItem(iPoint pos)
{

	//NOTE: thinking of using srand for more equally distributed random generation
	//NOTE: have to change this, the random isn't equal at all. Even when there's a 60% to have no item, it almost always drops items
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (App->sm->level1 == App->sm->dungeon3)
	{
		rarity = RARITY_RARE;
	}

	else if (App->sm->level2 == App->sm->dungeon3)
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
}

//Spawn Player
void snDungeon3::SpawnPlayer()
{
	//Add Player
	int random = rand() % 4;
	if (random == 0)
		App->game->player->SetPosition({ 1619, 2240 });
	else if (random == 1)
		App->game->player->SetPosition({ -2461, 2195 });
	else if (random == 2)
		App->game->player->SetPosition({ -458, 1197 });
	else if (random == 3)
		App->game->player->SetPosition({ 416, 3076 });

	
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
		pos = { 1619, 2240 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 1)
	{
		pos = { -2461, 2195 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 2)
	{
		pos = { -458, 1197 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 3)
	{
		pos = { 416, 3076 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}

	//Add Enemies 1
	//161, 141
	if (random != 0 && random2 != 0)
	{
		pos = { 152, 71 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 71;
		}
	}
	if (random != 1 && random2 != 1)
	{
		pos = { 46, 170 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 170;
		}
	}

	if (random != 2 && random2 != 2)
	{
		pos = { 46, 70 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 70;
		}
	}
	if (random != 3 && random2 != 3)
	{
		pos = { 162, 142 };
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				to_add = AddEnemy(pos);
				entity_list.push_back(to_add);
				pos.y += 3;
			}
			pos.x += 2;
			pos.y = 142;
		}
	}
	
	//Add Enemies 2
	pos = { 73, 134 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 134;
	}

	pos = { 199, 164 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 164;
	}

	pos = { 46, 142 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 142;
	}

	pos = { 86, 83 };
	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			to_add = AddEnemy(pos);
			entity_list.push_back(to_add);
			pos.y += 4;
		}
		pos.x += 3;
		pos.y = 83;
	}

	
	//Add Enemies 3
	//Y lines
	pos = { 33, 112 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 3;
	}

	pos = { 127, 160 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 3;
	}

	pos = { 174, 60 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.y += 3;
	}

	
	//X lines
	pos = { 157, 173 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 110, 101 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 140, 93 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	pos = { 59, 49 };
	for (int i = 0; i < 3; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}

	//Add Enemies 4
	pos = { 29, 78 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 31, 81 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 80, 63 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 82, 66 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 103, 67 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 105, 70 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	
	pos = { 74, 110 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 76, 113 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 86, 119 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 88, 122 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 86, 170 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 88, 173 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 106, 151 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 108, 154 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);

	pos = { 183, 185 };
	for (int i = 0; i < 2; i++)
	{
		to_add = AddEnemy(pos);
		entity_list.push_back(to_add);
		pos.x += 3;
	}
	pos = { 185, 188 };
	to_add = AddEnemy(pos);
	entity_list.push_back(to_add);
	

	//Items
	DropItem({ 2083, 2472 });
	DropItem({ 1158, 1893 });
	DropItem({ 839, 1410 });
	DropItem({ -1161, 1051 });
	DropItem({ -1995, 2048 });
	DropItem({ 939, 3698 });

}

bool snDungeon3::Load(pugi::xml_node& node)
{
	pugi::xml_node entities = node.child("entities");

	pugi::xml_node entity = entities.child("entity");

	for (; entity; entity = entity.next_sibling("entity"))
	{
		iPoint pos = { 0, 0 };

		pos.x = entity.child("position").attribute("x").as_float();
		pos.y = entity.child("position").attribute("y").as_float();

		if ((ENTITY_TYPE)entity.attribute("type").as_int() == ENEMY)
		{

			pugi::xml_node enmy = entity.child("enemy");

			EntEnemy* enemy = (EntEnemy*)App->game->em->AddEnemy(pos, (ENEMY_TYPE)enmy.attribute("enemy_type").as_int(), 1);
			entity_list.push_back(enemy);

			enemy->HP_current = enmy.child("HP").attribute("current_HP").as_float();
			enemy->HP_max = enmy.child("HP").attribute("max_HP").as_float();

		}
	}

	return true;
}

bool snDungeon3::Save(pugi::xml_node& node) const
{
	pugi::xml_node entities = node.append_child("entities");

	list<Entity*>::const_iterator item = entity_list.cbegin();



	for (; item != entity_list.cend(); item++)
	{
		Entity* ent = (*item);

		pugi::xml_node entity = entities.append_child("entity");

		pugi::xml_node pos = entity.append_child("position");

		pos.append_attribute("x") = ent->position.x;
		pos.append_attribute("y") = ent->position.y;

		//Saving an Enemy
		if (ent->type == ENEMY)
		{
			EntEnemy* enemy = (EntEnemy*)ent;


			entity.append_attribute("type") = ENEMY;

			pugi::xml_node enmy = entity.append_child("enemy");

			enmy.append_attribute("enemy_type") = enemy->enemy_type;

			pugi::xml_node hp = enmy.append_child("HP");

			hp.append_attribute("current_HP") = enemy->HP_current;
			hp.append_attribute("max_HP") = enemy->HP_max;
		}
	}

	return true;
}