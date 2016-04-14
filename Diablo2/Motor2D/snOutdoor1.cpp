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
#include "Entities.h"

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



	//cow = App->tex->Load("textures/cow.png");
	SDL_Rect position = { 2, 2, 0, 0 };
	pos_cow = &position;
	SDL_Rect section = { 0, 0, 96, 120 };
	sect_cow = &section;
	
	sprite_cow = new Sprite(NULL, sect_cow, pos_cow);
	sprite_cow->texture = App->tex->Load("textures/cow.png");
	sprite_cow->positionMap.x = 3;
	sprite_cow->positionMap.y = 50;
	sprite_cow->positionMap.w = 0;
	sprite_cow->positionMap.h = 0;

	sprite_cow->sectionTexture.x = 0;
	sprite_cow->sectionTexture.y = 0;
	sprite_cow->sectionTexture.w = 96;
	sprite_cow->sectionTexture.h = 120;

	sprite_cow->vx = 3;
	sprite_cow->vy = 3;
	int* pet = &sprite_cow->vx;
	int* pet2 = &sprite_cow->vy;
	sprite_cow->prova(pet, pet2);
	sprite_cow->y = 1;

	//App->render->AddSpriteToList(sprite_cow);

	/*
	building->texture = App->tex->Load("textures/building.png");
	building->position.x = 30;
	building->position.y = 300;
	cow->section.x = 131;
	cow->section.y = 110;
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

		int a = rand() % 2;
		if (a == 0)
			App->em->Add(p, ENEMY_DEBUG);
		if (a == 1)
			App->em->Add(p, ENEMY_CRAWLER);
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
	
	App->render->AddSpriteToList(sprite_cow);
	





	/*const vector<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->size(); ++i)
	{
		iPoint pos = App->map->GetTileBlit(path->at(i).x, path->at(i).y);
		
		App->render->Blit(debug, pos.x, pos.y);
	}*/

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

