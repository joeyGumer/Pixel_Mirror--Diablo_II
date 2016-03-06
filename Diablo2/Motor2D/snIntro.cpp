#include "snIntro.h"


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
	return true;
}

bool snIntro::UnLoad()
{
	return true;
}