#include "j1SceneManager.h"


j1SceneManager::j1SceneManager()
{
}


j1SceneManager::~j1SceneManager()
{
}


// Called before render is available
bool j1SceneManager::Awake(pugi::xml_node& conf)
{
	return true;
}

//PreUpdate
bool j1SceneManager::PreUpdate()
{
	return true;
}

//Update
bool j1SceneManager::Update(float dt)
{
	return true;
}

//PostUpdate
bool j1SceneManager::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1SceneManager::CleanUp()
{
	return true;
}
