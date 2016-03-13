#include "snOutdoor1.h"
#include "j1App.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1SceneManager.h"
#include "snIntro.h"
#include "j1Map.h"
#include "j1Gui.h"


// Constructor
snOutdoor1::snOutdoor1() : j1Scene()
{}

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
	//Insert iterations for this scene here
	
	//

	//Map
	App->map->Draw();

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