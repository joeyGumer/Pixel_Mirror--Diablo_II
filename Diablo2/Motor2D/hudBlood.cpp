#include "hudBlood.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Gui.h"

//NOTE: PROVISIONAL 
#include "j1Fonts.h"
hudBlood::hudBlood()
{
	active = true;
}

hudBlood::~hudBlood()
{

}

bool hudBlood::Start()
{
	player = App->game->player;
	blood_current = 0;

	
	blood_label = App->gui->AddGuiLabel("0", NULL, { 10, 5 }, NULL,FONT_WHITE, this);
	hud_gui_elements.push_back(blood_label);

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