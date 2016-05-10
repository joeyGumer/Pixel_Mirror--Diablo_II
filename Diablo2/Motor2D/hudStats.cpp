#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "hudStats.h"
#include "j1Player.h"
#include "j1Game.h"
#include "j1Fonts.h"
hudStats::hudStats()
{

}

//Destructor
hudStats::~hudStats()
{

}

//Called before fist frame
bool hudStats::Start()
{
	active = false;
	
	

	SDL_Color backgroundColor = { 0, 0, 0, 0 };
	window = App->gui->AddGuiImage({ 0, 0 }, { 486, 434, 320, 430 }, NULL, this);
	hud_gui_elements.push_back(window);

	closebutton = App->gui->AddGuiImage({ 275, 364 }, { 285, 192, 38, 38 }, window, this);
	closebutton->active = false;
	hud_gui_elements.push_back(closebutton);

	//Name Player Stat
	name = App->gui->AddGuiImage({ 8, 8 }, { 779, 960, 175, 20 }, window, this);
	player_name = App->gui->AddGuiLabel("Vampire", NULL, { 40, 2 }, name, FONT_WHITE, backgroundColor, this);
	player_name->Center(true, true);
	hud_gui_elements.push_back(name);
	hud_gui_elements.push_back(player_name);

	//Experience Stat
	experience = App->gui->AddGuiImage({ 8, 32 }, { 779, 960, 175, 38 }, window, this);
	text.create("%i", App->game->player->blood_current);
	player_experience = App->gui->AddGuiLabel(text, NULL, { 2, 8 }, experience, FONT_WHITE, backgroundColor, this);
	player_experience->Center(true, true);

	hud_gui_elements.push_back(experience);
	hud_gui_elements.push_back(player_experience);
	
	//Vitality Stat
	vitality = App->gui->AddGuiImage({ 8, 82 }, { 779, 960, 67, 20 }, window, this);
	player_vitality_name = App->gui->AddGuiLabel("Vitality", App->font->stats, { 2, 2 }, vitality, FONT_WHITE, backgroundColor, this);
	player_vitality_name->Center(true, true);
	vitality_value = App->gui->AddGuiImage({ 76, 82 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->vit_final);
	player_vitality = App->gui->AddGuiLabel(text, App->font->description, { 13, 3 }, vitality_value, FONT_BLUE, backgroundColor, this);
	player_vitality->Center(true, true);

	hud_gui_elements.push_back(vitality);
	hud_gui_elements.push_back(player_vitality_name);
	hud_gui_elements.push_back(vitality_value);
	hud_gui_elements.push_back(player_vitality);

	//Strenght Stat
	strength = App->gui->AddGuiImage({ 8, 136 }, { 779, 960, 67, 20 }, window, this);
	player_strength_name = App->gui->AddGuiLabel("Strength", App->font->stats, { 2, 2 }, strength, FONT_WHITE, backgroundColor, this);
	player_strength_name->Center(true, true);
	strength_value = App->gui->AddGuiImage({ 76, 136 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->str_final);
	player_strength = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, strength_value, FONT_BLUE, backgroundColor, this);
	player_strength->Center(true, true);
	hud_gui_elements.push_back(strength);
	hud_gui_elements.push_back(player_strength_name);
	hud_gui_elements.push_back(strength_value);
	hud_gui_elements.push_back(player_strength);

	//Dexterity Stat
	dexterity = App->gui->AddGuiImage({ 8, 190 }, { 779, 960, 67, 20 }, window, this);
	player_dexterity_name = App->gui->AddGuiLabel("Dexterity", App->font->stats, { 4, 2 }, dexterity, FONT_WHITE, backgroundColor, this);
	player_dexterity_name->Center(true, true);
	dexterity_value = App->gui->AddGuiImage({ 76, 190 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->dex_final);
	player_dexterity = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, dexterity_value, FONT_BLUE, backgroundColor, this);
	player_dexterity->Center(true, true);
	hud_gui_elements.push_back(dexterity);
	hud_gui_elements.push_back(player_dexterity_name);
	hud_gui_elements.push_back(player_dexterity);
	hud_gui_elements.push_back(dexterity_value);

	//Intelligence Stat
	intelligence = App->gui->AddGuiImage({ 8, 242 }, { 779, 960, 67, 20 }, window, this);
	player_intelligence_name = App->gui->AddGuiLabel("Intelligence", App->font->stats, { 4, 2 }, intelligence, FONT_WHITE, backgroundColor, this);
	player_intelligence_name->Center(true, true);
	intelligence_value = App->gui->AddGuiImage({ 76, 242 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->int_final);
	player_intelligence = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, intelligence_value, FONT_BLUE, backgroundColor, this);
	player_intelligence->Center(true, true);
	
	hud_gui_elements.push_back(intelligence);
	hud_gui_elements.push_back(player_intelligence_name);
	hud_gui_elements.push_back(intelligence_value);
	hud_gui_elements.push_back(player_intelligence);

	//Luck Stat
	luck = App->gui->AddGuiImage({ 8, 296 }, { 779, 960, 67, 20 }, window, this);
	player_luck_name = App->gui->AddGuiLabel("Luck", App->font->stats, { 4, 2 }, luck, FONT_WHITE, backgroundColor, this);
	player_luck_name->Center(true, true);
	luck_value = App->gui->AddGuiImage({ 76, 296 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->luck_final);
	player_luck = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, luck_value, FONT_BLUE, backgroundColor, this);
	player_luck->Center(true, true);
	hud_gui_elements.push_back(luck);
	hud_gui_elements.push_back(player_luck_name);
	hud_gui_elements.push_back(luck_value);
	hud_gui_elements.push_back(player_luck);

	//Life Stat
	life = App->gui->AddGuiImage({ 160, 82 }, { 779, 960, 72, 20 }, window, this);
	life_name = App->gui->AddGuiLabel("Life", App->font->stats, { 4, 2 }, life, FONT_WHITE, backgroundColor, this);
	life_name->Center(true, true);
	life_1 = App->gui->AddGuiImage({ 230, 82 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->HP_current);
	current_life = App->gui->AddGuiLabel(text, App->font->description, { 8, 2 }, life_1, FONT_WHITE, backgroundColor, this);
	current_life->Center(true, true);
	life_2 = App->gui->AddGuiImage({ 272, 82 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->HP_max);
	life_max = App->gui->AddGuiLabel(text, App->font->description, { 8, 2 }, life_2, FONT_WHITE, backgroundColor, this);
	life_max->Center(true, true);
	hud_gui_elements.push_back(life);
	hud_gui_elements.push_back(life_name);
	hud_gui_elements.push_back(life_1);
	hud_gui_elements.push_back(current_life);
	hud_gui_elements.push_back(life_2);
	hud_gui_elements.push_back(life_max);

	//Stamina Stat
	stamina = App->gui->AddGuiImage({ 160, 108 }, { 779, 960, 72, 20 }, window, this);
	stamina_name = App->gui->AddGuiLabel("Stamina", App->font->stats, { 4, 2 }, stamina, FONT_WHITE, backgroundColor, this);
	stamina_name->Center(true, true);
	stamina_1 = App->gui->AddGuiImage({ 230, 108 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->ST_current);
	current_stamina = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, stamina_1, FONT_WHITE, backgroundColor, this);
	current_stamina->Center(true, true);
	stamina_2 = App->gui->AddGuiImage({ 272, 108 }, { 779, 960, 40, 20 }, window, this);
	text.create("%i", App->game->player->ST_max);
	stamina_max = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, stamina_2, FONT_WHITE, backgroundColor, this);
	stamina_max->Center(true, true);

	hud_gui_elements.push_back(stamina);
	hud_gui_elements.push_back(stamina_name);
	hud_gui_elements.push_back(stamina_1);
	hud_gui_elements.push_back(current_stamina);
	hud_gui_elements.push_back(stamina_2);
	hud_gui_elements.push_back(stamina_max);

	//Basic Attack Stat
	basicAttack = App->gui->AddGuiImage({ 160, 136 }, { 779, 960, 100, 20 }, window, this);
	basicAttack_name = App->gui->AddGuiLabel("Basic Attack", App->font->stats, { 4, 2 }, basicAttack, FONT_WHITE, backgroundColor, this);
	basicAttack_name->Center(true, true);
	basicAttack_value = App->gui->AddGuiImage({ 260, 136 }, { 779, 960, 48, 20 }, window, this);
	text.create("%i", App->game->player->basic_damage);
	player_basicAttack = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, basicAttack_value, FONT_WHITE, backgroundColor, this);
	player_basicAttack->Center(true, true);
	hud_gui_elements.push_back(basicAttack);
	hud_gui_elements.push_back(basicAttack_name);
	hud_gui_elements.push_back(basicAttack_value);
	hud_gui_elements.push_back(player_basicAttack);

	//Resistance Stat
	resistance = App->gui->AddGuiImage({ 174, 338 }, { 779, 960, 100, 20 }, window, this);
	resistance_name = App->gui->AddGuiLabel("Resistance", App->font->stats, { 4, 2 }, resistance, FONT_WHITE, backgroundColor, this);
	resistance_name->Center(true, true);
	resistance_value = App->gui->AddGuiImage({ 272, 338 }, { 779, 960, 48, 20 }, window, this);
	text.create("%i", App->game->player->basic_damage);
	player_resistance = App->gui->AddGuiLabel(text, App->font->description, { 13, 2 }, resistance_value, FONT_WHITE, backgroundColor, this);
	player_resistance->Center(true, true);
	hud_gui_elements.push_back(resistance);
	hud_gui_elements.push_back(resistance_name);
	hud_gui_elements.push_back(resistance_value);
	hud_gui_elements.push_back(player_resistance);
	window->Desactivate();

	return true;
}

//Called before each loop iteration
bool hudStats::PreUpdate()
{

	return true;
}

//Called each frame
bool hudStats::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudStats::PostUpdate()
{
	return true;
}


//Called before quitting
bool hudStats::CleanUp()
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
}

void hudStats::Activate()
{
	active = !active;

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->active = active;
	}
}

void hudStats::SetBloodLabel(int blood)
{
	text.create("%i",blood);
	player_experience->SetText(text);
	player_experience->Center(true, true);
}
void hudStats::SetStrengthLabel(int strenght)
{
	text.create("%i", strenght);
	player_strength->SetText(text);
	player_strength->Center(true, true);
}
void hudStats::SetDexterityLabel(int dexterity)
{
	text.create("%i", dexterity);
	player_dexterity->SetText(text);
	player_dexterity->Center(true, true);
}
void hudStats::SetVitalityLabel(int vitality)
{
	text.create("%i", vitality);
	player_vitality->SetText(text);
	player_vitality->Center(true, true);
}
void hudStats::SetIntelligenceLabel(int intelligence)
{
	text.create("%i", intelligence);
	player_intelligence->SetText(text);
	player_intelligence->Center(true, true);
}
void hudStats::SetLuckLabel(int luck)
{
	text.create("%i", luck);
	player_luck->SetText(text);
	player_luck->Center(true, true);
}
void hudStats::SetLifeLabel(int current, int max)
{
	text.create("%i", current);
	current_life->SetText(text);

	text.create("%i", max);
	life_max->SetText(text);
}
void hudStats::SetStaminaLabel(int current, int max)
{
	text.create("%i", current);
	current_stamina->SetText(text);


	text.create("%i", max);
	stamina_max->SetText(text);
}
void hudStats::SetBasicAttackLabel(int basicAttack)
{
	text.create("%i", basicAttack);
	player_basicAttack->SetText(text);

}
void hudStats::SetResistenceLabel(int resistence)
{
	text.create("%i", resistence);
	player_resistance->SetText(text);
}










//Called when there's a gui event
void hudStats::OnEvent(GuiElement* element, GUI_Event even)
{
	if (closebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			closebutton->SetTextureRect({ 324, 192, 38, 38 });
			closebutton_pressed = true;
		}
		break;
		}
	}
}