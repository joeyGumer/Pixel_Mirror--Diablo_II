#include "j1Player.h"


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
	return true;
}

// Called each loop iteration
void j1Player::Draw()
{

}

// Called before quitting
bool j1Player::CleanUp()
{
	return true;
}

