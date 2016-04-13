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

	imatge_vaca = App->tex->Load("textures/cow.png");
	SDL_Rect puta = { 0, 0, 0, 0 };
	pos = &puta;
	SDL_Rect pene = { 96, 120, 0, 0 };
	sect = &pene;


	hola = new Sprite(imatge_vaca, pos, sect);
	App->render->AddSpriteToList(hola);
	//hola->posisiomapa.x;
	//hola->textura;


	//int valor1 = 5;
	//int valor2 = 3;
	//hola = new Sprite(valor1,valor2);

	//int p1 = 96;
	//int p2 = 120;
	

	//hola->resta1 = valor1;
	//hola->resta2 = valor2;
	//int si = hola->resta(hola->prova, hola->prova2);
	//LOG("Valor %d", si);
	//hola->textura = App->tex->Load("textures/cow.png");
	//App->render->posarllista(hola);

	//hola->seccioTextura = {0};

	//hola->posisiomapa = {0,0};
	//hola->posisiomapa->y = 100;

	
	

//	hola->seccioTextura->x = 96;
	//hola->seccioTextura->y = 120;
	//hola->posisiomapa->x = 10;
	//hola->posisiomapa->y = 10;


	

	
	

	//NOTE: Test Sprites
	//Player
	//problem on texture reading
	/*cow->texture = App->tex->Load("textures/cow.png");
	cow->position.x = 10;
	cow->position.y = 50;
	cow->section.x = 96;
	cow->section.y = 120;

	building->texture = App->tex->Load("textures/building.png");
	building->position.x = 30;
	building->position.y = 300;
	cow->section.x = 131;
	cow->section.y = 110;*/

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
	
	
	//int x, y;


	
	//App->render->DrawSprite(hola);
	//App->render->Blit(hola->texture, hola->positionMap->x, hola->positionMap->y);

	App->render->Blit(hola->texture, hola->positionMap->x, hola->positionMap->y);



	//->render->PintarSprite(hola->textura,hola->posisiomapa,hola->seccioTextura);

	
	
	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		hola->positionMap->x += SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		hola->positionMap->x -= SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		hola->positionMap->y -= SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		hola->positionMap->y += SPEED * dt;
	}
	


	/*const vector<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->size(); ++i)
	{
		iPoint pos = App->map->GetTileBlit(path->at(i).x, path->at(i).y);
		
		App->render->Blit(debug, pos.x, pos.y);
	}*/


	//NOTE: Sprite Test
	//App->render->Blit2(cow);

	//App->render->Blit2(building);
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
/*problem on cow*/
/*
void snOutdoor1::PlayerInput(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)
	{
		cow->position.x += SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		cow->position.x -= SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		cow->position.y -= SPEED * dt;
	}

	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		cow->position.y += SPEED * dt;
	}

}
*/
