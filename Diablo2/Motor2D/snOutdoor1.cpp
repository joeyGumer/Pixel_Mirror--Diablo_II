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
#include "j1Enemy.h"

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

	//Map
	App->map->Load("test_map_swamp.tmx");

	return true;
}

// PreUpdate
bool snOutdoor1::PreUpdate()
{
	return true;
}

// Update
bool snOutdoor1::Update(float dt)
{	
	//Add Entity
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
	{
		iPoint p;
		p = App->input->GetMouseWorldPosition();
		App->em->Add(p, ENEMY_DEBUG);
	}

	//Map
	App->map->Draw();

	//Player
	
	//App->game->player->Draw();
	

	//Camera
	//Free movement only avaliable on debug mode
	/*
	if (App->debug)
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