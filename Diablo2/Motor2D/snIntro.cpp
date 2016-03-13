#include "snIntro.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "snOutdoor1.h"


snIntro::snIntro() :j1Scene()
{}


snIntro::~snIntro()
{}

// Called before render is available
bool snIntro::Awake(pugi::xml_node& conf)
{
	return true;
}

bool snIntro::Start()
{
	return true;
}

// PreUpdate
bool snIntro::PreUpdate()
{
	return true;
}

// Update
bool snIntro::Update(float dt)
{
	//Insert iterations for this scene here

	// NOTE1 : this is for testing the Scene Manager
	App->render->DrawQuad({ 100, 100, 100, 100 }, 255, 0, 0);
	// When pressing SPACE it changes to the scene outdoor1
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == true)
	{
		//The scene manager changes the scene to outdoor1
		App->sm->ChangeScene(App->sm->outdoor1);
	}
	//

	return true;
}

// PostUpdate
bool snIntro::PostUpdate()
{
	return true;
}

// Called before quitting
bool snIntro::CleanUp()
{
	return true;
}

void snIntro::OnEvent(GuiElement* element, GUI_Event even)
{	
}

//Load/UnLoad, called when the scene changes
bool snIntro::Load()
{
	Start();
	return true;
}

bool snIntro::UnLoad()
{
	CleanUp();
	return true;
}