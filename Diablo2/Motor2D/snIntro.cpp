#include "snIntro.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "snOutdoor1.h"
#include "j1Gui.h"


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
	pass = false;
	exit = false;

	//Play button
	play_button = App->gui->AddGuiImage({ 370, 210 }, { 0, 0, 270, 35 }, NULL, this);
	play_button->interactable = true;
	play_button->focusable = true;
	//play_button->draggable = true;
	//Exit button
	exit_button = App->gui->AddGuiImage({ 370, 570 }, { 0, 0, 270, 35 }, NULL, this);
	exit_button->interactable = true;
	exit_button->focusable = true;
	//exit_button->draggable = true;
	//Singleplayer text
	singleplayer = App->gui->AddGuiLabel("Single player", NULL, { 0, 0 }, play_button, this);
	singleplayer->Center(370, 210);
	//ExitdiabloII text
	exitdiabloII = App->gui->AddGuiLabel("Exit diablo II", NULL, { 0, 0 }, exit_button, this);
	exitdiabloII->Center(370, 570);

	
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

	/*
	// When pressing SPACE it changes to the scene outdoor1
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == true)
	{
		//The scene manager changes the scene to outdoor1
		App->sm->ChangeScene(App->sm->outdoor1);
	}
	//
	*/
	if (pass == true)
	{
		App->sm->ChangeScene(App->sm->outdoor1);
	}

	else if (exit == true)
	{
		//SDL_Quit();
	}

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
	// NOTA : hacer funci�n en UI que elimine un elemento de la lista(no por el nodo), quizas mejor aun si va por conjunto (para quitar todos los elementos de una escena
	App->gui->gui_elements.del(App->gui->gui_elements.At(App->gui->gui_elements.find(play_button)));
	App->gui->gui_elements.del(App->gui->gui_elements.At(App->gui->gui_elements.find(exit_button)));
	App->gui->gui_elements.del(App->gui->gui_elements.At(App->gui->gui_elements.find(singleplayer)));
	App->gui->gui_elements.del(App->gui->gui_elements.At(App->gui->gui_elements.find(exitdiabloII)));
	return true;
}

void snIntro::OnEvent(GuiElement* element, GUI_Event even)
{	
	//NOTE clicking the button could charge the scene, now sets the bool pass to true and changes it, I don't think it's bad, but I don't know if the other way is better or not.
	//Play button
	if (play_button == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			element->SetTextureRect({ 0, 36, 270, 35 });
			break;
		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			element->SetTextureRect({ 0, 0, 270, 35 });
			pass = true;
		}
			break;
		case EVENT_FOCUS_DOWN:
			element->SetTextureRect({ 0, 36, 270, 35 });
			break;
		case EVENT_FOCUS_UP:
			element->SetTextureRect({ 0, 0, 270, 35 });
			break;
		}
	}
	//Exit button
	if (exit_button == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
			element->SetTextureRect({ 0, 36, 270, 35 });
			break;
		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			element->SetTextureRect({ 0, 0, 270, 35 });
			exit = true;
		}
			break;
		case EVENT_FOCUS_DOWN:
			element->SetTextureRect({ 0, 36, 270, 35 });
			break;
		case EVENT_FOCUS_UP:
			element->SetTextureRect({ 0, 0, 270, 35 });
			break;
		}
	}
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