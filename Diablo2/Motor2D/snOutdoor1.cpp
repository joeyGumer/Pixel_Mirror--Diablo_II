#include "snOutdoor1.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1SceneManager.h"
#include "snIntro.h"
#include "j1Map.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1EntityManager.h"
#include "j1Pathfinding.h"
#include "Entity.h"
#include "j1Game.h"

// quit log en no debug
#include "p2Log.h"

using namespace std;

// Constructor
snOutdoor1::snOutdoor1() : j1Scene()
{
	name.create("outdoor1");
}

// Destructor
snOutdoor1::~snOutdoor1()
{}

// Called before render is available
bool snOutdoor1::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called the first frame
bool snOutdoor1::Start()
{
	//Music
	//NOTE : deactivated for debugging
	//App->audio->PlayMusic("audio/music/town1.ogg", 0);

	debug = App->tex->Load("maps/mini_path.png");
	
	//Map
	if(App->map->Load("map_swamp.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	//Entities
	iPoint p = { 190, 170 };
	entity_list.push_back(App->game->em->Add(p, ENEMY));
	p = { 0, 200 };
	entity_list.push_back(App->game->em->Add(p, ENEMY));
	p = { -140, 180 };
	entity_list.push_back(App->game->em->Add(p, ENEMY));
	//entity_list.push_back(App->em->Add({ 200, 130 }, ENEMY));
	//entity_list.push_back(App->em->Add({ 250, 50 }, ENEMY));
	//entity_list.push_back(App->em->Add({ 200, 100 }, ENEMY));


	//NOTE: Test Sprite

	/*
	SDL_Rect position = { 2, 2, 0, 0 };
	pos_cow = &position;
	SDL_Rect section = { 0, 0, 96, 120 };
	sect_cow = &section;
	
	sprite_cow = new Sprite(NULL, sect_cow, pos_cow);
	sprite_cow->texture = App->tex->Load("textures/cow.png");
	sprite_cow->positionMap.x = -100;
	sprite_cow->positionMap.y = 100;
	sprite_cow->positionMap.w = 0;
	sprite_cow->positionMap.h = 0;
	sprite_cow->y = 0;

	sprite_cow->sectionTexture.x = 0;
	sprite_cow->sectionTexture.y = 0;
	sprite_cow->sectionTexture.w = 0;
	sprite_cow->sectionTexture.h = 0;

	App->render->AddSpriteToList(sprite_cow);


	SDL_Rect positione = { 2, 2, 0, 0 };
	pos_enemy = &positione;
	SDL_Rect sectione = { 0, 0, 96, 120 };
	sect_enemy = &sectione;

	enemy = new Sprite(NULL, sect_enemy, pos_enemy);
	enemy->texture = App->tex->Load("textures/enemy1.png");
	enemy->positionMap.x = -100;
	enemy->positionMap.y = 150;
	enemy->positionMap.w = 0;
	enemy->positionMap.h = 0;

	enemy->sectionTexture.x = 0;
	enemy->sectionTexture.y = 0;
	enemy->sectionTexture.w = 0;
	enemy->sectionTexture.h = 0;
	enemy->y = -1;

	App->render->AddSpriteToList(enemy);
	
	SDL_Rect positionee = { 2, 2, 0, 0 };
	pos_enemy2 = &positionee;
	SDL_Rect sectionee = { 0, 0, 96, 120 };
	sect_enemy2 = &sectionee;

	enemy2 = new Sprite(NULL, sect_enemy2, pos_enemy2);
	enemy2->texture = App->tex->Load("textures/enemy1.png");
	enemy2->positionMap.x = -20;
	enemy2->positionMap.y = 130;
	enemy2->positionMap.w = 0;
	enemy2->positionMap.h = 0;

	enemy2->sectionTexture.x = 0;
	enemy2->sectionTexture.y = 0;
	enemy2->sectionTexture.w = 0;
	enemy2->sectionTexture.h = 0;
	enemy2->y = 1;

	App->render->AddSpriteToList(enemy2);
	*/
	

	
	return true;
}

// PreUpdate
bool snOutdoor1::PreUpdate()
{
	//NOTE: just to test the pathfinding
	// debug pathfing ------------------
	/*static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}*/
	//
	return true;
}

// Update
bool snOutdoor1::Update(float dt)
{	
	//NOTE: Debug feature so we can test entities
	//Add Entity
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		iPoint p;
		p = App->input->GetMouseWorldPosition();
		p.x += App->map->data.tile_width/2;
		p.y += App->map->data.tile_height/2;

		//int a = rand() % 2;
		//if (a == 0)
			App->game->em->Add(p, ENEMY);
		//if (a == 1)
			//App->em->Add(p, ENEMY_CRAWLER);
	}

	//Map
	App->map->Draw();
	
	//Player
	
	//App->game->player->Draw();
	
	//Camera
	//Free movement only avaliable on debug mode
	
	/*if (App->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			App->render->camera.x -= floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			App->render->camera.x += floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			App->render->camera.y -= floor(CAM_SPEED*dt);
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			App->render->camera.y += floor(CAM_SPEED*dt);
		}
	}*/

	//Pathfinding debug
	//NOTE: uncomment for testing pathfinding
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->GetTileBlit(p.x, p.y);

	App->render->Blit(debug, p.x, p.y);
	/*
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		sprite_cow->positionMap.x = sprite_cow->positionMap.x -= floor(CAM_SPEED*dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT)
	{
		sprite_cow->positionMap.x += floor(CAM_SPEED*dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT)
	{
		sprite_cow->positionMap.y -= floor(CAM_SPEED*dt);
	}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
	{
		sprite_cow->positionMap.y += floor(CAM_SPEED*dt);
	}
	*/



	/*
	
	const vector<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->size(); ++i)
	{
		iPoint pos = App->map->GetTileBlit(path->at(i).x, path->at(i).y);
		
		App->render->Blit(debug, pos.x, pos.y);
	}
	*/
	
	return true;
}

// PostUpdate
bool snOutdoor1::PostUpdate()
{
	return true;
}

// Called before quitting
bool snOutdoor1::CleanUp()
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
void snOutdoor1::OnEvent(GuiElement* element, GUI_Event even)
{

}

//Load
bool snOutdoor1::Load()
{
	Start();
	return true;
}

//UnLoad
bool snOutdoor1::UnLoad()
{
	CleanUp();
	return true;
}

