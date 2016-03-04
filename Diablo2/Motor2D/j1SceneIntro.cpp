#include "j1SceneIntro.h"


j1SceneIntro::j1SceneIntro()
{
}


j1SceneIntro::~j1SceneIntro()
{
}

// Called before render is available
bool j1SceneIntro::Awake(pugi::xml_node& conf)
{
	return true;
}

//PreUpdate
bool j1SceneIntro::PreUpdate()
{
	return true;
}

//Update
bool j1SceneIntro::Update(float dt)
{
	return true;
}

//PostUpdate
bool j1SceneIntro::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1SceneIntro::CleanUp()
{
	return true;
}