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
#include "j1Game.h"
#include "j1HUD.h"
#include "GuiMiniMap.h"
#include "hudMiniMap.h"
#include "snDungeon2.h"
#include "Item.h"
#include "EntItem.h"

// Constructor
snOutdoor2::snOutdoor2() :j1Scene(OUTDOOR_2)
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
	//App->game->HUD->minimap->minimap->textura_minimapa = App->tex->Load("maps/path.png");
	App->audio->PlayMusic("audio/music/tristram.ogg", 0);

	
	//SDL_Texture* mapa = NULL;
	//Creation of the minimap
	
	if (minimap_tex == NULL)
	{
		minimap_tex = App->tex->Load("maps/MiniMapoutdoor2.png");
		
	}
	App->game->HUD->minimap->minimap->image.outside_tex = minimap_tex;
	App->game->HUD->minimap->minimap->SetAlpha(App->game->HUD->minimap->minimap->image.outside_tex, 90);

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
	if (App->new_game)
	{
		SpawnPlayer();
	}

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
			if (portal && App->sm->GetCurrentScene() == App->sm->level1)
			{
				portal->destiny = App->sm->level2;
			}
			else if (portal && App->sm->GetCurrentScene() == App->sm->level2)
			{
				portal->destiny = App->sm->win;
			}

			p = App->map->WorldToMap(p.x, p.y);
			int i = 0;

			entity_list.push_back(portal);
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
bool snOutdoor2::LoadScene()
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
	Entity* ret = NULL;
	if (App->sm->level1 == App->sm->outdoor2)
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

	else if (App->sm->level2 == App->sm->outdoor2)
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

	else if (App->sm->level3 == App->sm->outdoor2)
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

Entity* snOutdoor2::AddBoss(iPoint pos)
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

void snOutdoor2::AddPortal(iPoint pos)
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
		if (App->sm->level1 == App->sm->outdoor2)
		{
			portal->SetDestiny(App->sm->level2);
		}

		else if (App->sm->level2 == App->sm->outdoor2)
		{
			//portal->destiny = App->sm->level3;
			portal->destiny = App->sm->win;
		}

		else if (App->sm->level3 == App->sm->outdoor2)
		{
			portal->destiny = App->sm->win;
		}
		entity_list.push_back(to_add);
	}
}

void snOutdoor2::DropItem(iPoint pos)
{
	//NOTE: thinking of using srand for more equally distributed random generation
	//NOTE: have to change this, the random isn't equal at all. Even when there's a 60% to have no item, it almost always drops items
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (App->sm->level1 == App->sm->outdoor2)
	{
		rarity = RARITY_RARE;
	}

	else if (App->sm->level2 == App->sm->outdoor2)
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
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 1)
	{
		pos = { -3041, 2106 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 2)
	{
		pos = { -224, 4200 };
		to_add = AddBoss(pos);
		entity_list.push_back(to_add);
	}
	else if (random2 == 3)
	{
		pos = { 2815, 2839 };
		to_add = AddBoss(pos);
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

	//Items
	DropItem({ -651, 1009 });
	DropItem({ 82, 2075 });
	DropItem({ -1780, 1403 });
	DropItem({ -1117, 3272 });
	DropItem({ 1096, 3679 });
	DropItem({ 1146, 3164 });
	DropItem({ 2399, 1849 });
}

bool snOutdoor2::Load(pugi::xml_node& node)
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

			enemy->level = enmy.attribute("level").as_int();

			enemy->HP_current = enmy.child("HP").attribute("current_HP").as_float();
			enemy->HP_max = enmy.child("HP").attribute("max_HP").as_float();


			bool dead = enmy.attribute("death").as_bool();

			if (dead)
			{
				enemy->blood_drop = 0;
				enemy->current_input = ENTITY_INPUT_DEATH;
			}

		}

		if ((ENTITY_TYPE)entity.attribute("type").as_int() == PORTAL)
		{
			EntPortal* portal = (EntPortal*)App->game->em->Add(pos, PORTAL);

			if (portal && App->sm->GetCurrentScene() == App->sm->level1)
			{
				portal->destiny = App->sm->level2;
			}
			else if (portal && App->sm->GetCurrentScene() == App->sm->level2)
			{
				portal->destiny = App->sm->win;
			}

			entity_list.push_back(portal);
		}

		if ((ENTITY_TYPE)entity.attribute("type").as_int() == ITEM)
		{
			pugi::xml_node itm = entity.child("item");

			Item* item = NULL;

			ITEM_TYPE tp = (ITEM_TYPE)itm.attribute("type").as_int();
			ITEM_RARITY rarity = (ITEM_RARITY)itm.attribute("rarity").as_int();

			item = App->game->CreateItem(tp, rarity, pos);


			item->DeleteBuffs();

			for (pugi::xml_node bff = itm.child("buff"); bff; bff = itm.next_sibling("buff"))
			{
				Buff* buff;
				buff = new Buff((PLAYER_ATTRIBUTE)bff.attribute("type").as_int(), bff.attribute("value").as_int());
				item->item_buffs.push_back(buff);
			}

			item->rect.x = itm.child("rect").attribute("x").as_int();
			item->rect.y = itm.child("rect").attribute("y").as_int();
			item->rect.w = itm.child("rect").attribute("w").as_int();
			item->rect.h = itm.child("rect").attribute("h").as_int();

			item->ent_item->sprite->section_texture = item->rect;
		}
	}

	return true;
}

bool snOutdoor2::Save(pugi::xml_node& node) const
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

			enmy.append_attribute("level") = enemy->level;

			pugi::xml_node hp = enmy.append_child("HP");

			hp.append_attribute("current_HP") = enemy->HP_current;
			hp.append_attribute("max_HP") = enemy->HP_max;

			enmy.append_attribute("death") = enemy->dead;


		}

		if (ent->type == PORTAL)
		{
			entity.append_attribute("type") = PORTAL;
		}

		if (ent->type == ITEM)
		{
			EntItem* item_ent = (EntItem*)ent;
			Item* item = item_ent->nexus;

			entity.append_attribute("type") = ITEM;

			pugi::xml_node itm = entity.append_child("item");

			itm.append_attribute("rarity") = item->rarity;
			itm.append_attribute("type") = item->type;

			pugi::xml_node rect = itm.append_child("rect");

			rect.append_attribute("x") = item->rect.x;
			rect.append_attribute("y") = item->rect.y;
			rect.append_attribute("w") = item->rect.w;
			rect.append_attribute("h") = item->rect.h;

			for (int i = 0; i < item->item_buffs.size(); i++)
			{
				pugi::xml_node buff = itm.append_child("buff");

				buff.append_attribute("type") = item->item_buffs[i]->attribute;
				buff.append_attribute("value") = item->item_buffs[i]->value;
			}

		}
	}

	return true;
}