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
	App->map->Load("iso.tmx");

	//NOTE: testing movement

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
	//Map
	App->map->Draw();

	//Player
	//NOTE: this is before we have player module operative
	//WARNING : it doesn't work for now
	
	App->player->Draw();
	/*App->render->Blit(player_tile, player_pos.x, player_pos.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		movement = true;

		final_pos = App->input->GetMouseWorldPosition();
		final_pos = App->map->GetTileWorld(final_pos.x, final_pos.y);
	}

	
	if (movement)
	{
		if (App->debug)
		{

			App->render->DrawLine(player_pos.x + App->map->data.tile_width/2, 
									player_pos.y + App->map->data.tile_height, 
									final_pos.x + App->map->data.tile_width/2,
									final_pos.y + App->map->data.tile_height,
									255, 0, 0);
		}
	}*/
    

	//Camera
	//Free movement only avaliable on debug mode

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
	}

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
{}

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