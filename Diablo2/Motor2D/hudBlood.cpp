#include "hudBlood.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Input.h"

hudBlood::hudBlood()
{
	name.create("hud_blood");
	active = true;
}

hudBlood::~hudBlood()
{

}

bool hudBlood::Start()
{
	blood_tmp = 1500;
	message_get = false;
	player = App->game->player;
	blood_current = 0;

	
	blood_label = App->gui->AddGuiLabel("0", NULL, { 10, 5 }, NULL,FONT_YELLOW2, this);
	hud_gui_elements.push_back(blood_label);

	hey_listen = App->gui->AddGuiLabel("You have enough Pure Blood to unlock a skill! Press S to open the Skill Tree.", App->font->stats, {11, 25}, NULL, FONT_WHITE, this);
	hey_listen->active = false;
	hud_gui_elements.push_back(hey_listen);

	return true;
}

bool hudBlood::PreUpdate()
{
	return true;
}

bool hudBlood::Update(float dt)
{
	return true;
}

bool hudBlood::PostUpdate()
{

	if (hey_listen->active == false)
	{
		if ((blood_current >= blood_tmp) && message_get == false)
		{
			blood_tmp = blood_tmp + 2000;
			hey_listen->active = true;
			message_get = true;
		}
	}

	if (message_get == true && App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		message_get = false;
		hey_listen->active = false;
	}

	return true;
}

bool hudBlood::CleanUp()
{
	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == hud_gui_elements[i])
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	hud_gui_elements.clear();

	return true;
	return true;
}

void hudBlood::IncreaseBlood(int blood)
{
	blood_current += blood;
	p2SString text;
	text.create("%i", blood_current);
	blood_label->SetText(text);
}

void hudBlood::SetBlood(int blood)
{
	blood_current = blood;
	p2SString text;
	text.create("%i", blood_current);
	blood_label->SetText(text);
}