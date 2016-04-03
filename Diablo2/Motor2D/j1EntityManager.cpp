#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Input.h"
#include "j1Enemy.h"
#include "j1Pathfinding.h"
#include "p2Log.h"
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
		iPoint p; 
		p = App->input->GetMouseWorldPosition();
		const j1Enemy* e = EntityOnMouse();

		if (e != NULL)
		{
			Remove(e->id);
		}
	}

	return true;
}

// Called each loop iteration
bool j1EntityManager::PostUpdate()
{
	// Entities drawing
	map<uint, j1Enemy*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); ++it)
		it->second->Draw();

	return true;
}

// Called before quitting
bool j1EntityManager::CleanUp()
{
	map<uint, j1Enemy*>::iterator it = active_entities.begin();
	for (; it != active_entities.end(); it++)
		delete it->second;

	it = inactive_entities.begin();
	for (; it != inactive_entities.end(); it++)
		delete it->second;

	active_entities.clear();
	inactive_entities.clear();

	return true;
}

// Add method
j1Enemy* j1EntityManager::Add(iPoint &pos, ENEMY_TYPE type)
{
	j1Enemy* enemy = NULL;
	iPoint tile_pos = App->map->WorldToMap(pos.x, pos.y);

	// Checking for another bricks already on the map_tile specified by argument pos.
	map<uint, j1Enemy*>::iterator it = active_entities.begin();

	for (; it != active_entities.end(); it++)
	{
		if (it->second->tile_pos == tile_pos)
			return enemy; // No entity is created!
	}

	//if (App->pathfinding->IsWalkable(tile_pos))	// Can we add a new entity on that tile? i.e. Is that tile walkable?
	//{
		switch (type)
		{
		case (ENEMY_DEBUG) :
			enemy = new EnemyDebug(pos, ++next_ID);
			break;
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, j1Enemy*>(next_ID, enemy));
	//}

	return enemy;
}

// Remove an entity using its ID
bool j1EntityManager::Remove(uint id)
{
	if (active_entities.erase(id) > 0)
	{
		j1Enemy* e = GetEntity(id);
		inactive_entities.insert(pair<uint, j1Enemy*>(id, e));

		return true;
	}
	return false;
}

// Return ID for the corresponding entity
j1Enemy* j1EntityManager::GetEntity(uint id)
{
	map<uint, j1Enemy*>::iterator it = active_entities.find(id);
	return (it != active_entities.end() ? it->second : NULL);
}

// WhichEntityOnMouse: Returns an entity under the mouse cursor
j1Enemy* j1EntityManager::EntityOnMouse()
{
	iPoint p = App->input->GetMouseWorldPosition();

	map<uint, j1Enemy*>::reverse_iterator rit = active_entities.rbegin();
	for (; rit != active_entities.rend(); ++rit)
	{
		if (p.x >= rit->second->dim.x &&
			p.x <= rit->second->dim.x + rit->second->dim.w &&
			p.y >= rit->second->dim.y &&
			p.y <= rit->second->dim.y + rit->second->dim.h)
			return rit->second;
	}
	return NULL;
}

