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

#include "EntEnemyCouncil.h"
#include "EntEnemyCrawler.h"
#include "EntEnemyWolf.h"
#include "EntEnemyShaman.h"
#include "EntEnemySummoner.h"
#include "EntEnemyIzual.h"
#include "EntEnemyAndariel.h"
#include "EntEnemyNest.h"

#include "j1ParticleManager.h"

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
	texture_list.push_back(wolf_idle);
	wolf_walk = App->tex->Load("textures/wolf_walk.png");
	texture_list.push_back(wolf_walk);
	wolf_death = App->tex->Load("textures/wolf_death.png");
	texture_list.push_back(wolf_death);
	wolf_attack = App->tex->Load("textures/wolf_attack.png");
	texture_list.push_back(wolf_attack);


	//Crawler
	crawler_idle = App->tex->Load("textures/crawler_idle.png");
	texture_list.push_back(crawler_idle);
	crawler_walk = App->tex->Load("textures/crawler_walk.png");
	texture_list.push_back(crawler_walk);
	crawler_death = App->tex->Load("textures/crawler_death.png");
	texture_list.push_back(crawler_death);
	crawler_attack = App->tex->Load("textures/crawler_attack.png");
	texture_list.push_back(crawler_attack);

	//Boss
	boss_idle = App->tex->Load("textures/boss_idle.png");
	texture_list.push_back(boss_idle);
	boss_walk = App->tex->Load("textures/boss_walk.png");
	texture_list.push_back(boss_walk);
	boss_death = App->tex->Load("textures/boss_death.png");
	texture_list.push_back(boss_death);
	boss_attack = App->tex->Load("textures/boss_attack.png");
	texture_list.push_back(boss_attack);
	boss_cast = App->tex->Load("textures/boss_cast.png");
	texture_list.push_back(boss_cast);

	//Boss Particles
	boss_particle = App->tex->Load("particles/Flame/GreenFire.png");
	texture_list.push_back(boss_particle);

	//Shaman
	shaman_idle = App->tex->Load("textures/shaman_idle.png");
	texture_list.push_back(shaman_idle);
	shaman_walk = App->tex->Load("textures/shaman_walk.png");
	texture_list.push_back(shaman_walk);
	shaman_death = App->tex->Load("textures/shaman_death.png");
	texture_list.push_back(shaman_death);
	shaman_attack = App->tex->Load("textures/shaman_attack.png");
	texture_list.push_back(shaman_attack);

	//Shaman Particles
	shaman_particle = App->tex->Load("particles/Burn/Building_Burn_1.png");
	texture_list.push_back(shaman_particle);

	//Summoner
	summoner_idle = App->tex->Load("textures/summoner_idle.png");
	texture_list.push_back(summoner_idle);
	summoner_walk = App->tex->Load("textures/summoner_walk.png");
	texture_list.push_back(summoner_walk);
	summoner_death = App->tex->Load("textures/summoner_death.png");
	texture_list.push_back(summoner_death);
	summoner_attack = App->tex->Load("textures/summoner_attack.png");
	texture_list.push_back(summoner_attack);

	//Summoner Particles
	summoner_particle = App->tex->Load("particles/Burn/Building_Burn_1.png");
	texture_list.push_back(summoner_particle);

	//Izual textures
	izual_idle = App->tex->Load("textures/izual_idle.png");
	texture_list.push_back(izual_idle);
	izual_walk = App->tex->Load("textures/izual_walk.png");
	texture_list.push_back(izual_walk);
	izual_attack = App->tex->Load("textures/izual_attack.png");
	texture_list.push_back(izual_attack);
	izual_cast = App->tex->Load("textures/izual_cast.png");
	texture_list.push_back(izual_cast);
	izual_death = App->tex->Load("textures/izual_death.png");
	texture_list.push_back(izual_death);

	//Izual particles
	izual_particle = App->tex->Load("particles/Burn/Building_Burn_1.png");
	texture_list.push_back(izual_particle);

	//Andariel textures
	andariel_idle = App->tex->Load("textures/andariel_idle.png");
	texture_list.push_back(andariel_idle);
	andariel_walk = App->tex->Load("textures/andariel_walk.png");
	texture_list.push_back(andariel_walk);
	andariel_attack = App->tex->Load("textures/andariel_attack.png");
	texture_list.push_back(andariel_attack);
	andariel_cast = App->tex->Load("textures/andariel_cast.png");
	texture_list.push_back(andariel_cast);
	andariel_death = App->tex->Load("textures/andariel_death.png");
	texture_list.push_back(andariel_death);

	//Andariel particles
	andariel_particle = App->tex->Load("particles/Burn/Building_Burn_1.png");
	texture_list.push_back(andariel_particle);

	//Nest textures
	nest_idle = App->tex->Load("textures/nest_idle.png");
	texture_list.push_back(nest_idle);
	nest_death = App->tex->Load("textures/nest_death.png");
	texture_list.push_back(nest_death);
	nest_cast = App->tex->Load("textures/nest_cast.png");
	texture_list.push_back(nest_cast);

	//Nest particles
	nest_particle = App->tex->Load("particles/Flame/GreenFire.png");
	texture_list.push_back(nest_particle);

	//Portal
	portal_tex = App->tex->Load("textures/portal.png");
	texture_list.push_back(portal_tex);
	
	enemy_name = App->gui->AddGuiLabel(" ", NULL, { 260, 0 }, NULL, FONT_WHITE, this);
	enemy_name->Desactivate();

	//Sounds
	crawler_attackfx = App->audio->LoadFx("audio/fx/VileChildAttack.ogg");
	crawler_gethitfx = App->audio->LoadFx("audio/fx/VileChildGetHit.ogg");
	crawler_deathfx = App->audio->LoadFx("audio/fx/VileChildDeath.ogg");

	wolf_attackfx = App->audio->LoadFx("audio/fx/WolfAttack.ogg");
	wolf_gethitfx = App->audio->LoadFx("audio/fx/WolfGetHit.ogg");
	wolf_deathfx = App->audio->LoadFx("audio/fx/WolfDeath.ogg");

	summoner_attackfx = App->audio->LoadFx("audio/fx/VampireAttack.ogg");
	summoner_gethitfx = App->audio->LoadFx("audio/fx/VampireGetHit.ogg");
	summoner_deathfx = App->audio->LoadFx("audio/fx/VampireDeath.ogg");

	shaman_attackfx = App->audio->LoadFx("audio/fx/FallenShamanRoar.ogg");
	shaman_gethitfx = App->audio->LoadFx("audio/fx/FallenShamanGetHit.ogg");
	shaman_deathfx = App->audio->LoadFx("audio/fx/FallenShamanDeath.ogg");

	//nest_attackfx = App->audio->LoadFx("audio/fx/VileChildAttack.ogg");
	//nest_gethitfx = App->audio->LoadFx("audio/fx/VileChildAttack.ogg");
	nest_deathfx = App->audio->LoadFx("audio/fx/BloodHawkNestDeath.ogg");

	izual_attackfx = App->audio->LoadFx("audio/fx/IzualAttack.ogg");
	izual_gethitfx = App->audio->LoadFx("audio/fx/IzualGetHit.ogg");
	izual_deathfx = App->audio->LoadFx("audio/fx/IzualDeath.ogg");

	council_attackfx = App->audio->LoadFx("audio/fx/CouncilAttack.ogg");
	council_gethitfx = App->audio->LoadFx("audio/fx/CouncilGetHit.ogg");
	council_deathfx = App->audio->LoadFx("audio/fx/CounilDeath.ogg");

	andariel_attackfx = App->audio->LoadFx("audio/fx/AndarielAttack.ogg");
	andariel_gethitfx = App->audio->LoadFx("audio/fx/AndarielGetHit.ogg");
	andariel_deathfx = App->audio->LoadFx("audio/fx/AndarielDeath.ogg");

	

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
			((EntEnemy*)ent)->total_width = 200 + ((EntEnemy*)ent)->HP_max;
			((EntEnemy*)ent)->xpos = 220 - ((((EntEnemy*)ent)->HP_max)/2);
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

	list<SDL_Texture*>::iterator item2 = texture_list.begin();
	for (; item2 != texture_list.end(); item2++)
		App->tex->UnLoad(item2._Ptr->_Myval);

	return true;
}

//Collision
void j1EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_PLAYER_PARTICLE)
	{
		Particle* part = NULL;
		list<Particle*>::iterator item = App->pm->particleList.begin();
		for (; item != App->pm->particleList.end(); item++)
		{
			if (item._Ptr->_Myval->collider == c2)
			{
				part = item._Ptr->_Myval;
			}
		}
		map<uint, Entity*>::iterator item2 = active_entities.begin();
		for (; item2 != active_entities.end(); item2++)
		{
			if (item2->second->collider == c1)
			{
				EntEnemy* en = (EntEnemy*)item2->second;
				if (en->dead == false && part != NULL)
				{
					en->TakeDamage(part->damage);
					en->agro_range += 100.0f;
					part->DestroyParticle();
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
		case (ITEM) :
			entity = new EntItem(pos, ++next_ID);
			break;
		case(PORTAL) :
			entity = new EntPortal(pos, ++next_ID);
			break;
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, Entity*>(next_ID, entity));
	}

	return entity;
}

Entity* j1EntityManager::AddEnemy(iPoint &pos, ENEMY_TYPE type, int level)
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
			entity = new EntEnemyWolf(pos, ++next_ID, level);
			break;

		case (ENEMY_CRAWLER) :
			entity = new EntEnemyCrawler(pos, ++next_ID, level);
			break;

		case (ENEMY_COUNCIL) :
			entity = new EntEnemyCouncil(pos, ++next_ID, level);
			break;
		case (ENEMY_SHAMAN) :
			entity = new EntEnemyShaman(pos, ++next_ID, level);
			break;
		case (ENEMY_SUMMONER) :
			entity = new EntEnemySummoner(pos, ++next_ID, level);
			break;
		case (ENEMY_IZUAL) :
			entity = new EntEnemyIzual(pos, ++next_ID, level);
			break;
		case (ENEMY_ANDARIEL) :
			entity = new EntEnemyAndariel(pos, ++next_ID, level);
			break;
		case (ENEMY_NEST) :
			entity = new EntEnemyNest(pos, ++next_ID, level);
			break;
		}

		// We add the new entity to the map of active entities. 
		active_entities.insert(pair<uint, Entity*>(next_ID, entity));
	}

	return entity;
}

Entity* j1EntityManager::AddEnemyMap(iPoint &pos, ENEMY_TYPE type, int level)
{
	Entity* entity = NULL;
	iPoint tile_pos = pos;

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
			entity = new EntEnemyWolf(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;

		case (ENEMY_CRAWLER) :
			entity = new EntEnemyCrawler(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;

		case (ENEMY_COUNCIL) :
			entity = new EntEnemyCouncil(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;
		case (ENEMY_SHAMAN) :
			entity = new EntEnemyShaman(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;
		case (ENEMY_SUMMONER) :
			entity = new EntEnemySummoner(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;
		case (ENEMY_IZUAL) :
			entity = new EntEnemyIzual(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;
		case (ENEMY_ANDARIEL) :
			entity = new EntEnemyAndariel(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
			break;
		case (ENEMY_NEST) :
			entity = new EntEnemyNest(App->map->MapToWorld(pos.x, pos.y), ++next_ID, level);
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

vector<EntEnemy*> j1EntityManager::EnemiesOnArea(iPoint &pos, int radius)
{
	vector<EntEnemy*> ret;

	map<uint, Entity*>::reverse_iterator item = active_entities.rbegin();
	for (; item != active_entities.rend(); ++item)
	{
		if (item->second->type != ENEMY)
		{
			continue;
		}
		else
		{
			if (((EntEnemy*)item->second)->current_action == ENTITY_DEATH)
				continue;

			EntEnemy* enemy = ((EntEnemy*)item->second);

			iPoint position = { int(enemy->position.x), int(enemy->position.y) };
			if (pos.DistanceTo(position) <= radius)
			{
				ret.push_back(enemy);
			}
		}
	}

	return ret;
}

