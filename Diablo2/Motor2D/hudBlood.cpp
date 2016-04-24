#include "hudBlood.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Gui.h"

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

	blood_label = App->gui->AddGuiLabel("0", NULL, { 10, 5 }, NULL, this);

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