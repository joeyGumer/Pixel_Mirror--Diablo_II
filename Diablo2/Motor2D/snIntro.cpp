#include "snIntro.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Input.h"
#include "j1FileSystem.h"
#include "snOutdoor1.h"
#include "snOutdoor2.h"
#include "snDungeon1.h"
#include "snDungeon2.h"
#include "snDungeon3.h"
#include "j1Gui.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Fonts.h"


snIntro::snIntro() :j1Scene(INTRO)
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
	//Music
	//NOTE : deactivated for debugging mode
	//App->audio->PlayMusic("audio/music/introedit.ogg", 0);

	App->new_game = false;

	pass = false;
	load = false;
	exit = false;

	//Gui Elements

	//Background
	background = App->gui->AddGuiImage({ -95, -40 }, {1829, 82, 800, 600}, NULL, this);
	intro_gui.push_back(background);

	//Title animation
	if (title == NULL)
		title = App->tex->Load("gui/NewTitle.png");

	for (int i = 0; i < 6; i++)
	{
		logo.SetFrames(0, 0 + 170*i, 400, 170, 5, 0);
	}
	logo.loop = true;
	logo.speed = 0.2f;

	titleAnim = App->gui->AddGuiAnimation({ 115, 0 }, logo, title, NULL, this);
	intro_gui.push_back(titleAnim);

	//New button
	new_button = App->gui->AddGuiButton({ 181, 280 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "New Game", NULL, this);
	intro_gui.push_back(new_button);

	//Play button
	play_button = App->gui->AddGuiButton({ 181, 320 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "Load Game", NULL, this);
	intro_gui.push_back(play_button);
	if (!App->fs->SaveFileExists())
	{
		play_button->active = false;
	}

	//Controls button
	controls_button = App->gui->AddGuiButton({ 181, 360 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "CONTROLS", NULL, this);
	intro_gui.push_back(controls_button);

	//Exit button
	exit_button = App->gui->AddGuiButton({ 181, 400 }, { 0, 0, 270, 35 }, { 0, 0, 270, 35 }, { 0, 36, 270, 35 }, "ExiT Diablo II", NULL, this);
	intro_gui.push_back(exit_button);

	//-----------
	
	//Controls Window

	controls_window = App->gui->AddGuiImage({ 150, 20 }, { 941, 82, 320, 350 }, NULL, this);
	intro_gui.push_back(controls_window);
	
	//PrimarySkill Label
	primary_skill_image = App->gui->AddGuiImage({ 140, 45 }, { 3450, 960, 160, 10 }, controls_window, this);
	primary_skill = App->gui->AddGuiLabel("LEFT CLICK", App->font->stats, { 0, 0 }, primary_skill_image, FONT_WHITE, this);
	primary_skill->Center(true, true);
	intro_gui.push_back(primary_skill);
	intro_gui.push_back(primary_skill_image);

	//SecondarySkill Label
	secondary_skill_image = App->gui->AddGuiImage({140, 68 }, { 3450, 960, 160, 10 }, controls_window, this);
	secondary_skill = App->gui->AddGuiLabel("RIGHT CLICK", App->font->stats, { 0, 0 }, secondary_skill_image, FONT_WHITE, this);
	secondary_skill->Center(true, true);
	intro_gui.push_back(secondary_skill);
	intro_gui.push_back(secondary_skill_image);

	//Potion 1 Label
	potion_image = App->gui->AddGuiImage({140, 91 }, { 3450, 960, 160, 10 }, controls_window, this);
	potion = App->gui->AddGuiLabel("1", App->font->stats, { 0, 0 }, potion_image, FONT_WHITE, this);
	potion->Center(true, true);
	intro_gui.push_back(potion);
	intro_gui.push_back(potion_image);

	//Potion 2 Label
	potion_two_image = App->gui->AddGuiImage({140, 113 }, { 3450, 960, 160, 10 }, controls_window, this);
	potion_two = App->gui->AddGuiLabel("2", App->font->stats, { 0, 0 }, potion_two_image, FONT_WHITE, this);
	potion_two->Center(true, true);
	intro_gui.push_back(potion_two);
	intro_gui.push_back(potion_two_image);

	//Potion 3 Label
	potion_three_image = App->gui->AddGuiImage({140, 136 }, { 3450, 960, 160, 10 }, controls_window, this);
	potion_three = App->gui->AddGuiLabel("3", App->font->stats, { 0, 0 }, potion_three_image, FONT_WHITE, this);
	potion_three->Center(true, true);
	intro_gui.push_back(potion_three);
	intro_gui.push_back(potion_three_image);

	//Potion 4 Label
	potion_four_image = App->gui->AddGuiImage({140, 159 }, { 3450, 960, 160, 10 }, controls_window, this);
	potion_four = App->gui->AddGuiLabel("4", App->font->stats, { 0, 0 }, potion_four_image, FONT_WHITE, this);
	potion_four->Center(true, true);
	intro_gui.push_back(potion_four);
	intro_gui.push_back(potion_four_image);

	//Inventory Label
	inventory_image = App->gui->AddGuiImage({140, 183 }, { 3450, 960, 160, 10 }, controls_window, this);
	inventory = App->gui->AddGuiLabel("I", App->font->stats, { 0, 0 }, inventory_image, FONT_WHITE, this);
	inventory->Center(true, true);
	intro_gui.push_back(inventory);
	intro_gui.push_back(inventory_image);

	//Stats Label
	stats_image = App->gui->AddGuiImage({140, 205 }, { 3450, 960, 160, 10 }, controls_window, this);
	stats = App->gui->AddGuiLabel("C", App->font->stats, { 0, 0 }, stats_image, FONT_WHITE, this);
	stats->Center(true, true);
	intro_gui.push_back(stats);
	intro_gui.push_back(stats_image);

	//Map Label
	map_image = App->gui->AddGuiImage({140, 225 }, { 3450, 960, 160, 10 }, controls_window, this);
	map = App->gui->AddGuiLabel("TAB", App->font->stats, { 0, 0 }, map_image, FONT_WHITE, this);
	map->Center(true, true);
	intro_gui.push_back(map);
	intro_gui.push_back(map_image);

	//Skill Tree Label
	skill_tree_image = App->gui->AddGuiImage({140, 247 }, { 3450, 960, 160, 10 }, controls_window, this);
	skill_tree = App->gui->AddGuiLabel("S", App->font->stats, { 0, 0 }, skill_tree_image, FONT_WHITE, this);
	skill_tree->Center(true, true);
	intro_gui.push_back(skill_tree);
	intro_gui.push_back(skill_tree_image);
	
	//Game Menu Label
	game_menu_image = App->gui->AddGuiImage({140, 268 }, { 3450, 960, 160, 10 }, controls_window, this);
	game_menu = App->gui->AddGuiLabel("ESC", App->font->stats, { 0, 0 }, game_menu_image, FONT_WHITE, this);
	game_menu->Center(true, true);
	intro_gui.push_back(game_menu);
	intro_gui.push_back(game_menu_image);

	//Run Label
	run_image = App->gui->AddGuiImage({140, 287 }, { 3450, 960, 160, 10 }, controls_window, this);
	run = App->gui->AddGuiLabel("R", App->font->stats, { 0, 0 }, run_image, FONT_WHITE, this);
	run->Center(true, true);
	intro_gui.push_back(run);
	intro_gui.push_back(run_image);

	close_controls = App->gui->AddGuiButton({ 200, 315 }, { 3450, 960, 100, 35 }, { 3450, 960, 100, 35 }, { 3450, 960, 100, 35 }, "Close", App->font->stats,  this,controls_window,FONT_YELLOW2);
	intro_gui.push_back(close_controls);
	controls_window->Desactivate();


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
	//Exit game quick
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		std::exit(0);
	}
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
		if (App->fs->SaveFileExists())
		{
			App->fs->DeleteSaveFile();
		}

		App->new_game = true;

		App->sm->RandomLevel();
		if (App->sm->level1)
		{
			App->sm->ChangeScene(App->sm->level1);
		}
	}

	else if (load == true)
	{
		App->sm->LoadGame();

		load = false;

	}

	else if (exit == true)
	{
		std::exit(0);
	}



	return true;
}

// PostUpdate
bool snIntro::PostUpdate()
{
	//Logo animation
	
	return true;
}

// Called before quitting
bool snIntro::CleanUp()
{
	// NOTA : hacer función en UI que elimine un elemento de la lista(no por el nodo), quizas mejor aun si va por conjunto (para quitar todos los elementos de una escena
	//deletes the elements from the scene from the gui_elements list
	//maybe just by deactivating the iteration of this elements is a good way, who knows, ask ric

	for (list<GuiElement*>::iterator item = intro_gui.begin(); item != intro_gui.end(); item++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == (*item))
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}
	
	intro_gui.clear();
	
	return true;
}

void snIntro::OnEvent(GuiElement* element, GUI_Event even)
{	
	//NOTE clicking the button could charge the scene, now sets the bool pass to true and changes it, I don't think it's bad, but I don't know if the other way is better or not.
	if (new_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			new_button->button_image.SetTextureRect(play_button->click_tex);
			iPoint label_pos = new_button->button_label.GetLocalPosition();
			label_pos.x -= 4;
			label_pos.y += 2;
			new_button->button_label.SetLocalPosition(label_pos);
		}
		break;

		case EVENT_MOUSE_EXIT:
		{
			new_button->button_image.SetTextureRect(play_button->idle_tex);
			new_button->button_label.Center(true, true);
		}
		break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			new_button->button_image.SetTextureRect(play_button->idle_tex);
			new_button->button_label.Center(true, true);
			pass = true;
		}
		break;
		}
	}

	//Play button
	if (play_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			play_button->button_image.SetTextureRect(play_button->click_tex);
			iPoint label_pos = play_button->button_label.GetLocalPosition();
			label_pos.x -= 4;
			label_pos.y += 2;
			play_button->button_label.SetLocalPosition(label_pos);
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			play_button->button_image.SetTextureRect(play_button->idle_tex);
			play_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			play_button->button_image.SetTextureRect(play_button->idle_tex);
			play_button->button_label.Center(true, true);
			load = true;
		}
			break;
		}
	}
	if (controls_button == element)
	{
		switch (even)
		{

		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			controls_button->button_image.SetTextureRect(controls_button->click_tex);
			controls_button->button_label.SetLocalPosition({ 75, 8 });
			
			if(controls_window->active)
				controls_window->Desactivate();
			else
				controls_window->Activate();
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			controls_button->button_image.SetTextureRect(controls_button->idle_tex);
			controls_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			controls_button->button_image.SetTextureRect(controls_button->idle_tex);
			controls_button->button_label.Center(true, true);
			
		}
			break;
		}
	}
	//Exit button
	if (close_controls == element)
	{
		if (EVENT_MOUSE_LEFTCLICK_DOWN == even )
		{

			controls_window->Desactivate();

		}
	}
	//Exit button
	if (exit_button == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			exit_button->button_image.SetTextureRect(exit_button->click_tex);
			//NOTE : put this coordinates at the config.
			exit_button->button_label.SetLocalPosition({ 50, 8 });
		}
			break;

		case EVENT_MOUSE_EXIT:
		{
			exit_button->button_image.SetTextureRect(exit_button->idle_tex);
			exit_button->button_label.Center(true, true);
		}
			break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			exit_button->button_image.SetTextureRect(exit_button->idle_tex);
			exit_button->button_label.Center(true, true);
			exit = true;
		}
			break;

		}
	}
}

//Load/UnLoad, called when the scene changes
bool snIntro::LoadScene()
{
	Start();
	return true;
}

bool snIntro::UnLoad()
{
	CleanUp();
	return true;
}