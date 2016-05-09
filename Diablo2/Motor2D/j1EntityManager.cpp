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
#include "EntEnemy.h"

#include "j1Textures.h"
#include "j1Collision.h"

#include "j1Gui.h"
//Provisional
#include "j1Fonts.h"
#include "j1Audio.h"

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
	//Wolf
	wolf_idle = App->tex->Load("textures/wolf.png");
	wolf_walk = App->tex->Load("textures/wolf_walk.png");
	wolf_death = App->tex->Load("textures/wolf_death.png");
	wolf_attack = App->tex->Load("textures/wolf_attack.png");


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

	//Sounds
	crawler_attackfx = App->audio->LoadFx("audio/fx/VileChildAttack.ogg");
	crawler_gethitfx = App->audio->LoadFx("audio/fx/VileChildGetHit.ogg");
	crawler_deathfx = App->audio->LoadFx("audio/fx/VileChildDeath.ogg");

	wolf_attackfx = App->audio->LoadFx("audio/fx/WolfAttack.ogg");
	wolf_gethitfx = App->audio->LoadFx("audio/fx/WolfGetHit.ogg");
	wolf_deathfx = App->audio->LoadFx("audio/fx/WolfDeath.ogg");

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
		if (pos.x > -cam.x - UPDATE_MARGIN && pos.x < -cam.x + cam.w + UPDATE_MARGIN &&
			pos.y > -cam.y - UPDATE_MARGIN && pos.y < -cam.y + cam.h + UPDATE_MARGIN)
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

			SDL_Rect cam = App->render->camera;
			fPoint pos = item->second->position;

			App->render->DrawQuad({ -cam.x - UPDATE_MARGIN, -cam.y - UPDATE_MARGIN, cam.w + UPDATE_MARGIN*2, cam.h + UPDATE_MARGIN*2 }, 255, 0, 0, 255, false);
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

	if (enemy_name)
		enemy_name->Desactivate();

	return true;
}

//Collision
void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_PARTICLE)
	{
		map<uint, Entity*>::iterator item = active_entities.begin();
		for (; item != active_entities.end(); item++)
		{
			if (item->second->collider == c1)
			{
				EntEnemy* en = (EntEnemy*)item->second;
				if (en->dead == false)
				{
					en->TakeDamage(50);
					en->agro_range += 100.0f;
				}	
			}
		}
	}
}

// Add method

Entity* j1EntityManager::Add(iPoint &pos, ENTITY_TYPE type)
{
	Entity* entity = NULL;
	iPoint tile_pos = App->map->WorldToMap(pos.x, pos.y);

	// Checking for another bricks already on the map_tile specified by argument pos.
	map<uint, Entity*>::iterator item = active_entities.begin();

	//NOTE: disabled for now, because the items doesn't care if there's an entity
	/*for (; item != active_entities.end(); item++)
	{
		if (EntityOnCoords(pos) != NULL)
			return entity; // No entity is created!
	}*/

	if (App->pathfinding->IsWalkable(tile_pos))	// Can we add a new entity on that tile? i.e. Is that tile walkable?
	{
		switch (type)
		{
		//NOTE: to diferentiate the kinds of enemies, put ENEMY_TYPE enum, but don't use the one from the diferent kinds of entities
		case (ENEMY) :
			entity = new EntEnemyWolf(pos, ++next_ID);
			break;
		case (ITEM) :
			entity = new EntItem(pos, ++next_ID);
			break;
		case(PORTAL) :
			entity = new EntPortal(pos, ++next_ID);
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, Entity*>(next_ID, entity));
	}

	return entity;
}

Entity* j1EntityManager::AddEnemy(iPoint &pos, ENEMY_TYPE type)
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
		case (ENEMY_WOLF) :
			entity = new EntEnemyWolf(pos, ++next_ID);
			break;

		case (ENEMY_CRAWLER) :
			entity = new EntEnemyCrawler(pos, ++next_ID);
			break;

		case (ENEMY_COUNCIL) :
			entity = new EntEnemyCouncil(pos, ++next_ID);
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
		if (item->second->type == ENEMY)
			if (((EntEnemy*)item->second)->current_action == ENTITY_DEATH)
				continue;

			SDL_Rect rect = item->second->GetPlayerRect();

		if (pos.x >= rect.x && pos.x <= rect.x + rect.w &&
			pos.y >= rect.y && pos.y <= rect.y + rect.h)
			return item->second;
	}
	return NULL;
}


