#include "j1Player.h"
#include "j1Render.h"
#include "j1Textures.h"
//NOTE: doubts about including the map to player
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "SDL/include/SDL.h"

j1Player::j1Player()
{
}

//Destructor
j1Player::~j1Player()
{
}

// Called before render is available
bool j1Player::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called the first frame
bool j1Player::Start()
{
	player_debug = App->tex->Load("maps/path.png");
	

	//Idle sprites
	player_sprite = App->tex->Load("textures/vamp_idle.png");
	//NOTE : put this in a function
	//it will be an animation, but for now, it will be with rect
	idle_front = { 0, 0, 96, 92 };
	idle_left_front = { 0, 93, 96, 92 };
	//idle_left &= NULL;
	idle_left_back = { 0, 279, 96, 92 };
	//idle_back = NULL;
	idle_right_back = { 0, 465, 96, 92 };
	//idle_right = NULL;
	idle_right_front = { 0, 651, 96, 92 };

	current_sprite = idle_front;

	//
	player_pos = { 20, 20 };
	return true;
}

//PreUpdate
bool j1Player::PreUpdate()
{
	
	return true;
}

//Update
bool j1Player::Update(float dt)
{
	//NOTE: provisional movement for the player
	//NOTE: and provisional state machine for the player
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		current_sprite = idle_left_back;
		player_pos.x -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		current_sprite = idle_right_front;
		player_pos.x += 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		current_sprite = idle_right_back;
		player_pos.y -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		current_sprite = idle_left_front;
		player_pos.y += 1;
	}
	//

	//Camera idea to put it with an event, so it just iterates when it moves, see it later when we have done the pathfinding
	//Create the variable pivot because it will be more needed
	//NOTe : maybe is a good
	iPoint pos = App->map->MapToWorld(player_pos.x, player_pos.y);
	pos.x += App->map->data.tile_width/2;
	pos.y += App->map->data.tile_height/2;
	App->render->CenterCamera(pos.x, pos.y);
	//NOTE: Add a debug to see the pivot

	return true;
}

//PostUpdate
bool j1Player::PostUpdate()
{
	
	return true;
}

// Called each loop iteration
//NOTE, in fact, we don't need this here
void j1Player::Draw() const
{
	//Debug Player Render
	//NOTE: provisional quad player
	//App->render->DrawQuad({ pos_x - 25, pos_y - 25, 50, 50 }, 255, 0, 0);
	//pos_x - 25 & pos_y - 25 set the pivot on the middle of the "sprite", because it is 100 pixels long (50/2 = 25)
	iPoint pos = App->map->MapToWorld(player_pos.x, player_pos.y);

	//Draw player
	App->render->Blit(player_sprite, pos.x, pos.y, &current_sprite);
}

// Called before quitting
bool j1Player::CleanUp()
{
	return true;
}

