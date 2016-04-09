#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Input.h"
#include "Entities.h"
#include "j1Pathfinding.h"
#include "p2Log.h"
#include "j1Map.h"
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
	}

	return true;
}

// Called each loop iteration
bool j1EntityManager::PostUpdate()
{
	// Entities drawing
	map<uint, Entity*>::iterator item = active_entities.begin();
	for (; item != active_entities.end(); ++item)
	{
		if (App->debug)
		{
			item->second->DrawDebug();
		}

		item->second->Draw();
	}	

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
		if (item->second->tile_pos == tile_pos)
			return entity; // No entity is created!
	}

	if (App->pathfinding->IsWalkable(tile_pos))	// Can we add a new entity on that tile? i.e. Is that tile walkable?
	{
		switch (type)
		{
		case (ENEMY_DEBUG) :
			entity = new entEnemyDebug(pos, ++next_ID);
			break;
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, Entity*>(next_ID, entity));
	}

	return entity;
}

// Remove an entity using its ID
bool j1EntityManager::Remove(uint id)
{
	if (active_entities.erase(id) > 0)
	{
		Entity* e = GetEntity(id);
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

	map<uint, Entity*>::reverse_iterator item = active_entities.rbegin();
	for (; item != active_entities.rend(); ++item)
	{
		if (p.x >= item->second->GetPlayerRect().x &&
			p.x <= item->second->GetPlayerRect().x + item->second->GetPlayerRect().w &&
			p.y >= item->second->GetPlayerRect().y &&
			p.y <= item->second->GetPlayerRect().y + item->second->GetPlayerRect().h)
			return item->second;
	}
	return NULL;
}

