#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Input.h"
#include "EntEnemy.h"
#include "j1Pathfinding.h"
#include "p2Log.h"
#include "j1Map.h"

#include "j1Render.h"
#include "EntItem.h"
#include "EntPortal.h"

#include "j1Textures.h"
#include "j1Collision.h"

#include "j1Gui.h"
//Provisional
#include "j1Fonts.h"

#include <algorithm>


j1EntityManager::j1EntityManager() : j1Module()
{
	name.create("EntityManager");
}

// Destructor
j1EntityManager::~j1EntityManager()
{
	next_ID = 0;
}

// Called before render is available
bool j1EntityManager::Awake(pugi::xml_node &node)
{
	return true;
}

// Called before the first frame
bool j1EntityManager::Start()
{
	//Crawler
	crawler_idle = App->tex->Load("textures/crawler_idle.png");
	crawler_walk = App->tex->Load("textures/crawler_walk.png");
	crawler_death = App->tex->Load("textures/crawler_death.png");
	crawler_attack = App->tex->Load("textures/crawler_attack.png");

	//Boss
	boss_idle = App->tex->Load("textures/boss_idle.png");
	boss_walk = App->tex->Load("textures/boss_walk.png");
	boss_death = App->tex->Load("textures/boss_death.png");
	boss_attack = App->tex->Load("textures/boss_attack.png");

	//Portal
	portal_tex = App->tex->Load("textures/portal.png");
	
	enemy_name = App->gui->AddGuiLabel(" ", NULL, { 260, 0 }, NULL, FONT_WHITE, this);
	enemy_name->Desactivate();

	return true;
}

// Called each loop iteration
bool j1EntityManager::PreUpdate()
{
	// Clicking middle button, eliminates an entity
	if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
	{
		iPoint pos; 
		pos = App->input->GetMouseWorldPosition();
		const Entity* entity = EntityOnMouse();

		if (entity != NULL)
		{
			Remove(entity->id);
		}
	}


	return true;
}

//Update
bool j1EntityManager::Update(float dt)
{
	map<uint, Entity*>::iterator item = active_entities.begin();
	for (; item != active_entities.end(); ++item)
	{
		SDL_Rect cam = App->render->camera;
		fPoint pos = item->second->position;
		if (pos.x + 100 > -cam.x && pos.x - 100 < -cam.x + cam.w &&
			pos.y + 100 > -cam.y && pos.y - 100 < -cam.y + cam.h)
		{
			item->second->Update(dt);
		}
	}

	// Entities drawing
	item = active_entities.begin();
	for (; item != active_entities.end(); ++item)
	{
		item->second->Draw();
		if (App->debug)
		{
			item->second->DrawDebug();
		}

	}

	if (Entity* ent = EntityOnMouse())
	{
		if (ent->type == ENEMY)
		{
			((EntEnemy*)ent)->DrawHPbar();
			enemy_name->Activate();
			enemy_name->SetText(((EntEnemy*)ent)->name);
			enemy_name->Center(true, false);
		}
	}
	else
		enemy_name->Desactivate();

	return true;
}

// Called each loop iteration
bool j1EntityManager::PostUpdate()
{

	//Checking if there's an entity under the mouse to do it's stuff
	// NOTE: put it as gui


	return true;
}

// Called before quitting
bool j1EntityManager::CleanUp()
{
	map<uint, Entity*>::iterator item = active_entities.begin();
	for (; item != active_entities.end(); item++)
		delete item->second;

	item = inactive_entities.begin();
	for (; item != inactive_entities.end(); item++)
		delete item->second;

	active_entities.clear();
	inactive_entities.clear();

	enemy_name->Desactivate();

	return true;
}

// Add method

Entity* j1EntityManager::Add(iPoint &pos, ENTITY_TYPE type)
{
	Entity* entity = NULL;
	iPoint tile_pos = App->map->WorldToMap(pos.x, pos.y);

	// Checking for another bricks already on the map_tile specified by argument pos.
	map<uint, Entity*>::iterator item = active_entities.begin();

	for (; item != active_entities.end(); item++)
	{
		if (EntityOnCoords(pos) != NULL)
			return entity; // No entity is created!
	}

	if (App->pathfinding->IsWalkable(tile_pos))	// Can we add a new entity on that tile? i.e. Is that tile walkable?
	{
		switch (type)
		{
		//NOTE: to diferentiate the kinds of enemies, put ENEMY_TYPE enum, but don't use the one from the diferent kinds of entities
		case (ENEMY) :
			entity = new EntEnemyWolf(pos, ++next_ID);
			break;

		case (ENEMY_CRAWLER) :
			entity = new EntEnemyCrawler(pos, ++next_ID);
			break;

		case (ENEMY_BOSS) :
			entity = new EntEnemyBoss(pos, ++next_ID);
			break;
		case (ITEM_HEALTH) :
			entity = new itmPotionHP(pos, ++next_ID);
			break;
		case(PORTAL) :
			entity = new EntPortal(pos, ++next_ID);
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, Entity*>(next_ID, entity));
	}

	return entity;
}

// Remove an entity using its ID
bool j1EntityManager::Remove(uint id)
{
	//NOTE: has to delete, not do this!
	//It's not destroyed? we'll see for later weeks
	Entity* e = GetEntity(id);
	if (e && e->collider)
		e->collider->to_delete = true;

	if (e && e->sprite)
	{
		//NOTE: here, is a beautiful memory leak, if i uncomment this all the game goes fucked

		//RELEASE(e->sprite);
		App->render->sprites.remove(e->sprite);
		//RELEASE(e->sprite);
	}

	if (active_entities.erase(id) > 0)
	{
		Entity* e = GetEntity(id);
		//NOTE: has to delete, not do this!
		//It's not destroyed? we'll see for later weeks
		inactive_entities.insert(pair<uint, Entity*>(id, e));

		return true;
	}
	return false;
}

// Return ID for the corresponding entity
Entity* j1EntityManager::GetEntity(uint id)
{
	map<uint, Entity*>::iterator item = active_entities.find(id);
	return (item != active_entities.end() ? item->second : NULL);
}

// WhichEntityOnMouse: Returns an entity under the mouse cursor
Entity* j1EntityManager::EntityOnMouse()
{
	iPoint p = App->input->GetMouseWorldPosition();

	return EntityOnCoords(p);
}

Entity* j1EntityManager::EntityOnCoords(iPoint &pos)
{
	map<uint, Entity*>::reverse_iterator item = active_entities.rbegin();
	for (; item != active_entities.rend(); ++item)
	{
		//NOTE: Have to be specified to just Enemy....
		if (item->second->type == ENEMY || item->second->type == ENEMY_CRAWLER || item->second->type == ENEMY_BOSS)
			if (((EntEnemy*)item->second)->current_action == ENTITY_DEATH)
				continue;

			SDL_Rect rect = item->second->GetPlayerRect();

		if (pos.x >= rect.x && pos.x <= rect.x + rect.w &&
			pos.y >= rect.y && pos.y <= rect.y + rect.h)
			return item->second;
	}
	return NULL;
}


