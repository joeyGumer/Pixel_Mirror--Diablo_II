#include "j1Player.h"
#include "j1Render.h"
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

//PreUpdate
bool j1Player::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		pos_x -= 2;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		pos_x += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		pos_y -= 2;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		pos_y += 2;
	}
	return true;
}

//Update
bool j1Player::Update(float dt)
{

	return true;
}

//PostUpdate
bool j1Player::PostUpdate()
{
	//Center Camera
	App->render->CenterCamera(pos_x, pos_y);
	//Draw Character
	Draw();
	return true;
}

// Called each loop iteration
void j1Player::Draw()
{
	//Debug Player Render
	App->render->DrawQuad({ pos_x - 25, pos_y - 25, 50, 50 }, 255, 0, 0);
	//pos_x - 25 & pos_y - 25 set the pivot on the middle of the "sprite", because it is 100 pixels long (50/2 = 25)
}

// Called before quitting
bool j1Player::CleanUp()
{
	return true;
}

