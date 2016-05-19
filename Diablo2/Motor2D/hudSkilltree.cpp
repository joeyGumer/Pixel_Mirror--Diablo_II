#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "hudSkilltree.h"
#include "j1Game.h"
#include "j1Player.h"
#include "PlayerSkills.h"
#include "j1Fonts.h"



hudSkilltree::hudSkilltree()
{

}

//Destructor
hudSkilltree::~hudSkilltree()
{

}

//Called before fist frame
bool hudSkilltree::Start()
{
	active = false;
	p2SString text;
	player = App->game->player;

	//skillpoints = 15;
	//lionpoints = clawpoints = swordspoints = handpoints = starpoints = fireballpoints = projectilespoints = manpoints = cogpoints = heartjawpoints = batwingpoints = wolfpoints = fangspoints = bigjawpoints = bloodmanpoints = 0;
	


	//NOTE: the cooldown has to be an int. There are some skill where the blood charges increasing up is not an int either, it needs to be an int.
	//Night summoning ---------------------------------------------------------------------------

	nightsummoning = App->gui->AddGuiImage({ 321, 216 }, { 1449, 588, 320, 216 }, NULL, this);
	nightsummoning->active = false;
	hud_gui_elements.push_back(nightsummoning);

	bloodbutton = App->gui->AddGuiImage({ 230, 0 }, { 1678, 588, 90, 108 }, nightsummoning, this);
	bloodbutton->active = false;
	hud_gui_elements.push_back(bloodbutton);


	//Skills
	clotted_blood_skin = App->gui->AddGuiSkill({ 82, 9 }, { 537, 920, 48, 48 }, { 390, 871, 48, 48 }, player->clotted_blood, nightsummoning, this);
	clotted_blood_skin->active = false;
	hud_gui_elements.push_back(clotted_blood_skin);

	raise_wolf = App->gui->AddGuiSkill({ 152, 9 }, { 488, 969, 48, 48 }, { 390, 969, 48, 48 }, player->shadow_walker, nightsummoning, this);
	raise_wolf->active = false;
	hud_gui_elements.push_back(raise_wolf);

	//text2.create("%i", player->shadow_walker->price);
	price11 = App->gui->AddGuiLabel("1500", NULL, { 0, 45 }, raise_wolf, FONT_WHITE, this);
	price11->active = false;
	hud_gui_elements.push_back(price11);

	//text2.create("%i", player->clotted_blood->price);
	price12 = App->gui->AddGuiLabel("2000", NULL, { 0, 45 }, clotted_blood_skin, FONT_WHITE, this);
	price12->active = false;
	hud_gui_elements.push_back(price12);

	bat_girl = App->gui->AddGuiSkill({ 15, 77 }, { 537, 969, 48, 48 }, { 341, 1018, 48, 48 }, player->night_ward, nightsummoning, this);
	bat_girl->active = false;
	hud_gui_elements.push_back(bat_girl);

	raise_blood_hawk = App->gui->AddGuiSkill({ 82, 77 }, { 586, 969, 48, 48 }, { 390, 1018, 48, 48 }, player->lust, nightsummoning, this);
	raise_blood_hawk->active = false;
	raise_blood_hawk->skill_parents.push_back(clotted_blood_skin->skill);
	hud_gui_elements.push_back(raise_blood_hawk);

	blood_golem = App->gui->AddGuiSkill({ 152, 145 }, { 635, 969, 48, 48 }, { 439, 1018, 48, 48 }, player->undead, nightsummoning, this);
	blood_golem->active = false;
	blood_golem->skill_parents.push_back(raise_blood_hawk->skill);
	blood_golem->skill_parents.push_back(raise_wolf->skill);
	hud_gui_elements.push_back(blood_golem);

	//--------------------------------------------------------------------------------------------
	

	//Martial blood ---------------------------------------------------------------------------
	martialblood = App->gui->AddGuiImage({ 321, 0 }, { 807, 434, 320, 216 }, NULL, this);
	martialblood->active = false;
	hud_gui_elements.push_back(martialblood);

	skill_points_img = App->gui->AddGuiImage({ 251, 56 }, { 1176,540, 49, 27 }, martialblood, this);
	skill_points_img->active = false;
	hud_gui_elements.push_back(skill_points_img);

	skillpoints_label = App->gui->AddGuiLabel("0", NULL, { 265, 62 }, skill_points_img, FONT_WHITE, this);
	skillpoints_label->active = false;
	hud_gui_elements.push_back(skillpoints_label);

	//Skills
	stinging_strike = App->gui->AddGuiSkill({ 154, 14 }, { 488, 871, 48, 48 }, { 390, 724, 48, 48 }, player->stinging_strike, martialblood, this);
	stinging_strike->active = false;
	hud_gui_elements.push_back(stinging_strike);

	wild_talon = App->gui->AddGuiSkill({ 84, 14 }, { 439, 871, 48, 48 }, { 341, 724, 48, 48 }, player->wild_talon, martialblood, this);
	wild_talon->active = false;
	hud_gui_elements.push_back(wild_talon);

	bat_strike = App->gui->AddGuiSkill({ 154, 82 }, { 586, 871, 48, 48 }, { 390, 773, 48, 48 }, player->bat_strike, martialblood, this);
	bat_strike->active = false;
	bat_strike->skill_parents.push_back(stinging_strike->skill);
	hud_gui_elements.push_back(bat_strike);
	
	soul_of_ice = App->gui->AddGuiSkill({ 84, 150 }, { 635, 871, 48, 48 }, { 341, 822, 48, 48 }, player->soul_of_ice, martialblood, this);
	soul_of_ice->active = false;
	soul_of_ice->skill_parents.push_back(wild_talon->skill);
	hud_gui_elements.push_back(soul_of_ice);

	krobus_arts = App->gui->AddGuiSkill({ 15, 82 }, { 537, 871, 48, 48 }, { 341, 773, 48, 48 }, player->krobus_arts, martialblood, this);
	krobus_arts->active = false;
	hud_gui_elements.push_back(krobus_arts);

	//Delete button
	martialdeletebutton = App->gui->AddGuiImage({ 20, 165 }, { 285, 192, 38, 38 }, martialblood, this);
	martialdeletebutton->active = false;
	hud_gui_elements.push_back(martialdeletebutton);
	//------------------------------------------------------------------------------------------


	//Blood spells -----------------------------------------------------------------------------
	bloodspells = App->gui->AddGuiImage({ 321, 216 }, { 807, 651, 320, 216 }, NULL, this);
	bloodspells->active = false;
	hud_gui_elements.push_back(bloodspells);

	nightbutton = App->gui->AddGuiImage({ 230, 103 }, { 1037, 754, 90, 112 }, bloodspells, this);
	nightbutton->active = false;
	hud_gui_elements.push_back(nightbutton);

	//Skills
	blood_arrow = App->gui->AddGuiSkill({ 14, 16 }, { 439, 920, 48, 48 }, { 390, 822, 48, 48 }, player->blood_arrow, bloodspells, this);
	blood_arrow->active = false;
	hud_gui_elements.push_back(blood_arrow);

	vampire_breath = App->gui->AddGuiSkill({ 84, 16 }, { 488, 920, 48, 48 }, { 341, 871, 48, 48 }, player->vampire_breath, bloodspells, this);
	vampire_breath->active = false;
	hud_gui_elements.push_back(vampire_breath);

	blood_bomb = App->gui->AddGuiSkill({ 14, 138 }, { 586, 920, 48, 48 }, { 341, 920, 48, 48 }, player->blood_bomb, bloodspells, this);
	blood_bomb->active = false;
	blood_bomb->skill_parents.push_back(blood_arrow->skill);
	hud_gui_elements.push_back(blood_bomb);

	red_feast = App->gui->AddGuiSkill({ 83, 138 }, { 635, 920, 48, 48 }, { 390, 920, 48, 48 }, player->red_feast, bloodspells, this);
	red_feast->active = false;
	red_feast->skill_parents.push_back(blood_arrow->skill);
	red_feast->skill_parents.push_back(vampire_breath->skill);
	hud_gui_elements.push_back(red_feast);

	heard_of_bats = App->gui->AddGuiSkill({ 152, 70 }, { 439, 969, 48, 48 }, { 341, 969, 48, 48 }, player->heard_of_bats, bloodspells, this);
	heard_of_bats->active = false;
	hud_gui_elements.push_back(heard_of_bats);
	

	//Prices -------------------------------------------------------------------------------------------------------------------------
	p2SString text2;

	//text2.create("%i", player->stinging_strike->price);
	price1 = App->gui->AddGuiLabel("1500", NULL, { 0, 45 }, stinging_strike, FONT_WHITE, this);
	price1->active = false;
	hud_gui_elements.push_back(price1);

	//text2.create("%i", player->wild_talon->price);
	price2 = App->gui->AddGuiLabel("1500", NULL, { 0, 45 }, wild_talon, FONT_WHITE, this);
	price2->active = false;
	hud_gui_elements.push_back(price2);

	//text2.create("%i", player->bat_strike->price);
	price3 = App->gui->AddGuiLabel("2500", NULL, { 0, 45 }, bat_strike, FONT_WHITE, this);
	price3->active = false;
	hud_gui_elements.push_back(price3);

	//text2.create("%i", player->soul_of_ice->price);
	price4 = App->gui->AddGuiLabel("2500", NULL, { 0, 45 }, soul_of_ice, FONT_WHITE, this);
	price4->active = false;
	hud_gui_elements.push_back(price4);

	//text2.create("%i", player->krobus_arts->price);
	price5 = App->gui->AddGuiLabel("2000", NULL, { 0, 45 }, krobus_arts, FONT_WHITE, this);
	price5->active = false;
	hud_gui_elements.push_back(price5);

	//text2.create("%i", player->blood_arrow->price);
	price6 = App->gui->AddGuiLabel("1500", NULL, { 0, 45 }, blood_arrow, FONT_WHITE, this);
	price6->active = false;
	hud_gui_elements.push_back(price6);

	//text2.create("%i", player->vampire_breath->price);
	price7 = App->gui->AddGuiLabel("1500", NULL, { 0, 45 }, vampire_breath, FONT_WHITE, this);
	price7->active = false;
	hud_gui_elements.push_back(price7);

	//text2.create("%i", player->blood_bomb->price);
	price8 = App->gui->AddGuiLabel("2500", NULL, { 0, 45 }, blood_bomb, FONT_WHITE, this);
	price8->active = false;
	hud_gui_elements.push_back(price8);

	//text2.create("%i", player->red_feast->price);
	price9 = App->gui->AddGuiLabel("2500", NULL, { 0, 45 }, red_feast, FONT_WHITE, this);
	price9->active = false;
	hud_gui_elements.push_back(price9);

	//text2.create("%i", player->heard_of_bats->price);
	price10 = App->gui->AddGuiLabel("2000", NULL, { 0, 45 }, heard_of_bats, FONT_WHITE, this);
	price10->active = false;
	hud_gui_elements.push_back(price10);
	
	//GuiTexts --------------------------------------------------------------------------------------------
	//Night summoning ---------------------------------------------------------------------------
	
	vector<StringColor> clottedtext;
	clottedtext.push_back(StringColor("CloTTed Blood skin", FONT_VIOLET));
	clottedtext.push_back(StringColor("ImprovemenT: reduces The damage Taken", FONT_WHITE));
	text.create("%i", player->clotted_blood->price);
	text.Insert(0, "pure BLOOD COST: ");
	clottedtext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->clotted_blood->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges COST: ");
	clottedtext.push_back(StringColor(text, FONT_PURPLE));
	clottedtext.push_back(StringColor("duraTion: 3 seconds", FONT_BLUE));
	/*
	text.create("%i", player->clotted_blood->buff.time);
	text.Insert(0, "duraTion: ");
	clottedtext.push_back(StringColor(text, FONT_BLUE));
	*/
	clottedtext.push_back(StringColor("Cooldown: 10 seconds", FONT_BLUE));
	/*
	text.create("%i", player->clotted_blood->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	clottedtext.push_back(StringColor(text, FONT_BLUE));
	*/
	text.create("%i", player->clotted_blood->buff.value);
	text.Insert(0, "ARMOR: ");
	clottedtext.push_back(StringColor(text, FONT_GREEN));
	text.create("%i", player->clotted_blood->buff.attribute);
	text.Insert(0, "reduced damage: ");
	clottedtext.push_back(StringColor(text, FONT_GREEN));
	clotted_blood_skin->text = App->gui->AddGuiText({ 0, 0 }, clottedtext, clotted_blood_skin, this);
	clotted_blood_skin->text->Desactivate();
	texts.push_back(clotted_blood_skin->text);
	hud_gui_elements.push_back(clotted_blood_skin->text);
	clottedtext.clear();

	vector<StringColor> wolftext;
	wolftext.push_back(StringColor("shadows walker", FONT_VIOLET));
	wolftext.push_back(StringColor("ImprovemenT: makes you invisible", FONT_WHITE));
	text.create("%i", player->shadow_walker->price);
	text.Insert(0, "pure BLOOD COST: ");
	wolftext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->shadow_walker->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges COST: ");
	wolftext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->shadow_walker->buff.value);
	text.Insert(0, "duraTion: ");
	wolftext.push_back(StringColor(text, FONT_BLUE));
	wolftext.push_back(StringColor("Cooldown: 10 seconds", FONT_BLUE));
	/*
	text.create("%i", player->shadow_walker->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	wolftext.push_back(StringColor(text, FONT_BLUE));
	*/
	raise_wolf->text = App->gui->AddGuiText({ 0, 0 }, wolftext, raise_wolf, this);
	raise_wolf->Desactivate();
	texts.push_back(raise_wolf->text);
	hud_gui_elements.push_back(raise_wolf->text);
	wolftext.clear();

	vector<StringColor> batgirltext;
	batgirltext.push_back(StringColor("baT girl", FONT_VIOLET));
	batgirltext.push_back(StringColor("unavailable", FONT_RED));
	bat_girl->text = App->gui->AddGuiText({ 0, 0 }, batgirltext, bat_girl, this);
	bat_girl->Desactivate();
	texts.push_back(bat_girl->text);
	hud_gui_elements.push_back(bat_girl->text);
	batgirltext.clear();

	vector<StringColor> hawktext;
	hawktext.push_back(StringColor("raise blood hawk", FONT_VIOLET));
	hawktext.push_back(StringColor("unavailable", FONT_RED));
	raise_blood_hawk->text = App->gui->AddGuiText({ 0, 0 }, hawktext, raise_blood_hawk, this);
	raise_blood_hawk->Desactivate();
	texts.push_back(raise_blood_hawk->text);
	hud_gui_elements.push_back(raise_blood_hawk->text);
	hawktext.clear();

	vector<StringColor> golemtext;
	golemtext.push_back(StringColor("blood golem", FONT_VIOLET));
	golemtext.push_back(StringColor("unavailable", FONT_RED));
	blood_golem->text = App->gui->AddGuiText({ 0, 0 }, golemtext, blood_golem, this);
	blood_golem->Desactivate();
	texts.push_back(blood_golem->text);
	hud_gui_elements.push_back(blood_golem->text);
	golemtext.clear();

	//Martial blood ---------------------------------------------------------------------------
	vector<StringColor> stingtext;
	stingtext.push_back(StringColor("STinging sTrike", FONT_VIOLET));
	stingtext.push_back(StringColor("charge-up skill: powerful sTrike", FONT_WHITE));
	text.create("%i", player->stinging_strike->price);
	text.Insert(0, "pure BLOOD COST: ");
	stingtext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->stinging_strike->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges addiTion: ");
	stingtext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->stinging_strike->life_cost_base);
	text.Insert(0, "life cosT: ");
	stingtext.push_back(StringColor(text, FONT_RED));
	text.create("%i-%i", player->stinging_strike->base_damage_down, player->stinging_strike->base_damage_up);
	text.Insert(0, "Damage: ");
	stingtext.push_back(StringColor(text, FONT_GREEN));
	stingtext.push_back(StringColor("Cooldown: 1 seconds", FONT_BLUE));
	/*
	text.create("%i", player->stinging_strike->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	stingtext.push_back(StringColor(text, FONT_BLUE));
	*/
	stinging_strike->text = App->gui->AddGuiText({ 0, 45 }, stingtext, stinging_strike, this);
	stinging_strike->text->Desactivate();
	texts.push_back(stinging_strike->text);
	hud_gui_elements.push_back(stinging_strike->text);
	stingtext.clear();
	
	vector<StringColor> talontext;
	talontext.push_back(StringColor("wild Talon", FONT_VIOLET));
	talontext.push_back(StringColor("charge-up skill: powerful kick", FONT_WHITE));
	text.create("%i", player->wild_talon->price);
	text.Insert(0, "pure BLOOD COST: ");
	talontext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->wild_talon->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges addiTion: ");
	talontext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->wild_talon->life_cost_base);
	text.Insert(0, "life cosT: ");
	talontext.push_back(StringColor(text, FONT_RED));
	text.create("%i-%i", player->wild_talon->base_damage_down, player->wild_talon->base_damage_up);
	text.Insert(0, "Damage: ");
	talontext.push_back(StringColor(text, FONT_GREEN));
	talontext.push_back(StringColor("Cooldown: 2 seconds", FONT_BLUE));
	/*
	text.create("%i", player->wild_talon->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	talontext.push_back(StringColor(text, FONT_BLUE));
	*/
	wild_talon->text = App->gui->AddGuiText({ 0, 45 }, talontext, wild_talon, this);
	wild_talon->Desactivate();
	texts.push_back(wild_talon->text);
	hud_gui_elements.push_back(wild_talon->text);
	talontext.clear();

	vector<StringColor> battext;
	battext.push_back(StringColor("baT sTrike", FONT_VIOLET));
	battext.push_back(StringColor("Finishing move: powerful kick ThaT heals", FONT_WHITE));
	text.create("%i", player->bat_strike->price);
	text.Insert(0, "pure BLOOD COST: ");
	battext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->bat_strike->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges cosT: ");
	battext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->bat_strike->life_cost_base);
	text.Insert(0, "life sTeal: ");
	battext.push_back(StringColor(text, FONT_GREEN));
	text.create("%i-%i", player->bat_strike->base_damage_down, player->bat_strike->base_damage_up);
	text.Insert(0, "Damage: ");
	battext.push_back(StringColor(text, FONT_GREEN));
	battext.push_back(StringColor("Cooldown: 3 seconds", FONT_BLUE));
	/*
	text.create("%i", player->bat_strike->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	battext.push_back(StringColor(text, FONT_BLUE));
	*/
	bat_strike->text = App->gui->AddGuiText({ -20, 20 }, battext, bat_strike, this);
	bat_strike->Desactivate();
	texts.push_back(bat_strike->text);
	hud_gui_elements.push_back(bat_strike->text);
	battext.clear();

	vector<StringColor> icetext;
	icetext.push_back(StringColor("soul of ice", FONT_VIOLET));
	icetext.push_back(StringColor("Finishing move: kick ThaT slows The enemies", FONT_WHITE));
	text.create("%i", player->soul_of_ice->price);
	text.Insert(0, "pure BLOOD COST: ");
	icetext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->soul_of_ice->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges cosT: ");
	icetext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i-%i", player->soul_of_ice->base_damage_down, player->soul_of_ice->base_damage_up);
	text.Insert(0, "Damage: ");
	icetext.push_back(StringColor(text, FONT_GREEN));
	icetext.push_back(StringColor("duraTion: 3 seconds", FONT_BLUE));
	icetext.push_back(StringColor("Cooldown: 3 seconds", FONT_BLUE));
	/*
	text.create("%i", player->soul_of_ice->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	icetext.push_back(StringColor(text, FONT_BLUE));
	*/
	soul_of_ice->text = App->gui->AddGuiText({ 0, 0 }, icetext, soul_of_ice, this);
	soul_of_ice->Desactivate();
	texts.push_back(soul_of_ice->text);
	hud_gui_elements.push_back(soul_of_ice->text);
	icetext.clear();

	vector<StringColor> krobustext;
	krobustext.push_back(StringColor("krobus arTs", FONT_VIOLET));
	krobustext.push_back(StringColor("Improvement: nexT basic aTTacks are more powerful", FONT_WHITE));
	text.create("%i", player->krobus_arts->price);
	text.Insert(0, "pure BLOOD COST: ");
	krobustext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->krobus_arts->life_cost_base);
	text.Insert(0, "life cosT: ");
	krobustext.push_back(StringColor(text, FONT_RED));
	text.create("%i", player->krobus_arts->damage_bonus_base);
	text.Insert(0, "Damage: ");
	krobustext.push_back(StringColor(text, FONT_GREEN));
	krobustext.push_back(StringColor("duraTion: 3 seconds", FONT_BLUE));
	krobustext.push_back(StringColor("Cooldown: 10 seconds", FONT_BLUE));
	/*
	text.create("%i", player->krobus_arts->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	krobustext.push_back(StringColor(text, FONT_BLUE));
	*/
	krobus_arts->text = App->gui->AddGuiText({ 0, 10 }, krobustext, krobus_arts, this);
	krobus_arts->Desactivate();
	texts.push_back(krobus_arts->text);
	hud_gui_elements.push_back(krobus_arts->text);
	krobustext.clear();

	//Blood spells ---------------------------------------------------------------------------
	vector<StringColor> arrowtext;
	arrowtext.push_back(StringColor("blood arrow", FONT_VIOLET));
	arrowtext.push_back(StringColor("charge-up skill: Throws a blood projecTile aT The chosen direcTion", FONT_WHITE));
	text.create("%i", player->blood_arrow->price);
	text.Insert(0, "pure BLOOD COST: ");
	arrowtext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->blood_arrow->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges addiTion: ");
	arrowtext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->blood_arrow->life_cost_base);
	text.Insert(0, "life cosT: ");
	arrowtext.push_back(StringColor(text, FONT_RED));
	text.create("%i-%i", player->blood_arrow->base_damage_down, player->blood_arrow->base_damage_up);
	text.Insert(0, "spell Damage: ");
	arrowtext.push_back(StringColor(text, FONT_GREEN));
	arrowtext.push_back(StringColor("Cooldown: 1.5 seconds", FONT_BLUE));
	/*
	text.create("%i", player->blood_arrow->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	arrowtext.push_back(StringColor(text, FONT_BLUE));
	*/
	blood_arrow->text = App->gui->AddGuiText({ 0, 0 }, arrowtext, blood_arrow, this);
	blood_arrow->Desactivate();
	texts.push_back(blood_arrow->text);
	hud_gui_elements.push_back(blood_arrow->text);
	arrowtext.clear();

	vector<StringColor> breathtext;
	breathtext.push_back(StringColor("vampire breaTh", FONT_VIOLET));
	breathtext.push_back(StringColor("finishing move: projecTiles Thrown doing a cone", FONT_WHITE));
	text.create("%i", player->vampire_breath->price);
	text.Insert(0, "pure BLOOD COST: ");
	breathtext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->vampire_breath->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges cosT: ");
	breathtext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i-%i", player->vampire_breath->base_damage_down, player->vampire_breath->base_damage_up);
	text.Insert(0, "spells Damage: ");
	breathtext.push_back(StringColor(text, FONT_GREEN));
	breathtext.push_back(StringColor("Cooldown: 10 seconds", FONT_BLUE));
	/*
	text.create("%i", player->vampire_breath->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	breathtext.push_back(StringColor(text, FONT_BLUE));
	*/
	text.create("%i", player->vampire_breath->range);
	text.Insert(0, "range: ");
	breathtext.push_back(StringColor(text, FONT_GREEN));
	vampire_breath->text = App->gui->AddGuiText({ 0, 0 }, breathtext, vampire_breath, this);
	vampire_breath->Desactivate();
	texts.push_back(vampire_breath->text);
	hud_gui_elements.push_back(vampire_breath->text);
	breathtext.clear();

	vector<StringColor> bombtext;
	bombtext.push_back(StringColor("blood bomb", FONT_VIOLET));
	bombtext.push_back(StringColor("charge-up skill: Throws a projecTile ThaT deals area damage on hiT", FONT_WHITE));
	text.create("%i", player->blood_bomb->price);
	text.Insert(0, "pure BLOOD COST: ");
	bombtext.push_back(StringColor(text, FONT_YELLOW));
	bombtext.push_back(StringColor("blood charges addiTion: 18", FONT_PURPLE));
	/*
	text.create("%i", player->blood_bomb->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges addiTion: ");
	bombtext.push_back(StringColor(text, FONT_PURPLE));
	*/
	text.create("%i", player->blood_bomb->life_cost_base);
	text.Insert(0, "life cosT: ");
	bombtext.push_back(StringColor(text, FONT_RED));
	//Blood bomb needs a damage and an area variable
	text.create("%i-%i", player->blood_arrow->base_damage_down, player->blood_arrow->base_damage_up);
	text.Insert(0, "spell Damage: ");
	bombtext.push_back(StringColor(text, FONT_GREEN));
	bombtext.push_back(StringColor("Cooldown: 3 seconds", FONT_BLUE));
	bombtext.push_back(StringColor("area: 100", FONT_GREEN));
	/*
	text.create("%i", player->blood_bomb->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	bombtext.push_back(StringColor(text, FONT_BLUE));
	*/
	blood_bomb->text = App->gui->AddGuiText({ 0, 0 }, bombtext, blood_bomb, this);
	blood_bomb->Desactivate();
	texts.push_back(blood_bomb->text);
	hud_gui_elements.push_back(blood_bomb->text);
	bombtext.clear();

	vector<StringColor> feasttext;
	feasttext.push_back(StringColor("red feasT", FONT_VIOLET));
	feasttext.push_back(StringColor("finishing move: absorbs The life of The enemies found wiThin iTs area", FONT_WHITE));
	feasttext.push_back(StringColor("you cannoT move while The abiliTy is acTive", FONT_WHITE));
	text.create("%i", player->red_feast->price);
	text.Insert(0, "pure BLOOD COST: ");
	feasttext.push_back(StringColor(text, FONT_YELLOW));
	feasttext.push_back(StringColor("Blood charges (per second): 20", FONT_PURPLE));
	/*
	text.create("%i", player->red_feast->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges cosT (per second): ");
	feasttext.push_back(StringColor(text, FONT_PURPLE));
	*/
	text.create("%i-%i", player->red_feast->base_damage_down, player->red_feast->base_damage_up);
	text.Insert(0, "spell Damage (per second): ");
	feasttext.push_back(StringColor(text, FONT_GREEN));
	text.create("%i", player->red_feast->life_steal_base);
	text.Insert(0, "life sTeal : ");
	feasttext.push_back(StringColor(text, FONT_GREEN));
	feasttext.push_back(StringColor("Cooldown: 10 seconds", FONT_BLUE));
	/*
	text.create("%i", player->red_feast->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	feasttext.push_back(StringColor(text, FONT_BLUE));
	*/
	feasttext.push_back(StringColor("radius: 150", FONT_GREEN));
	/*
	text.create("%i", player->vampire_breath->radius);
	text.Insert(0, "radius: ");
	feasttext.push_back(StringColor(text, FONT_GREEN));
	*/
	red_feast->text = App->gui->AddGuiText({ -20, 0 }, feasttext, red_feast, this);
	red_feast->Desactivate();
	texts.push_back(red_feast->text);
	hud_gui_elements.push_back(red_feast->text);
	feasttext.clear();

	vector<StringColor> herdtext;
	herdtext.push_back(StringColor("herd of baTs", FONT_VIOLET));
	herdtext.push_back(StringColor("Finishing move: invokes baTs in an area and deal damage over Time", FONT_WHITE));
	text.create("%i", player->heard_of_bats->price);
	text.Insert(0, "pure BLOOD COST: ");
	herdtext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->heard_of_bats->blood_charge_increase_base);
	text.Insert(0, "BLOOD charges addiTion: ");
	herdtext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i-%i", player->heard_of_bats->base_damage_down, player->heard_of_bats->base_damage_up);
	text.Insert(0, "spell Damage (per second): ");
	herdtext.push_back(StringColor(text, FONT_GREEN));
	text.create("%i", player->heard_of_bats->time);
	text.Insert(0, "duraTion: ");
	herdtext.push_back(StringColor(text, FONT_BLUE));
	herdtext.push_back(StringColor("Cooldown: 15 seconds", FONT_BLUE));
	herdtext.push_back(StringColor("radius: 150", FONT_GREEN));
	/*
	text.create("%i", player->heard_of_bats->cooldown_base);
	text.Insert(0, "COOLDOWN: ");
	herdtext.push_back(StringColor(text, FONT_BLUE));
	
	text.create("%i", player->heard_of_bats->radius);
	text.Insert(0, "radius: ");
	herdtext.push_back(StringColor(text, FONT_GREEN));
	*/
	heard_of_bats->text = App->gui->AddGuiText({ -20, 0 }, herdtext, heard_of_bats, this);
	heard_of_bats->Desactivate();
	texts.push_back(heard_of_bats->text);
	hud_gui_elements.push_back(heard_of_bats->text);
	herdtext.clear();

	return true;
}

//Called before each loop iteration
bool hudSkilltree::PreUpdate()
{

	return true;
}

//Called each frame
bool hudSkilltree::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudSkilltree::PostUpdate()
{
	//Total skill points
	p2SString text;
	text.create("%i", player->blood_current);
	skillpoints_label->SetText(text);
	skillpoints_label->Center(true, true);
	

	return true;
}


//Called before quitting
bool hudSkilltree::CleanUp()
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
		
	texts.clear();

	hud_gui_elements.clear();
	return true;
}

void hudSkilltree::Activate()
{
	active = !active;

	for (int i = 0; i < hud_gui_elements.size(); i++)
	{
		hud_gui_elements[i]->active = active;
	}

	for (int i = 0; i < texts.size(); i++)
		texts[i]->Desactivate();

}

//Called when there's a gui event
void hudSkilltree::OnEvent(GuiElement* element, GUI_Event even)
{
	//Night summoning button
	if (nightbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			bloodspells->Desactivate();
			nightsummoning->Activate();
			
			for (int i = 0; i < texts.size(); i++)
				texts[i]->Desactivate();
				
		}
		break;
		}
	}

	//Blood spells button
	else if (bloodbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			nightsummoning->Desactivate();
			bloodspells->Activate();
			
			for (int i = 0; i < texts.size(); i++)
				texts[i]->Desactivate();
				
		}
		break;
		}
	}

	//Martial delete button
	else if (martialdeletebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
				martialdeletebutton->SetTextureRect({ 324, 192, 38, 38 });
				martialdeletebutton_pressed = true;
		}
		break;
		}
	}


	else if (element->type == GUI_SKILL)
	{

		if (even == EVENT_MOUSE_LEFTCLICK_DOWN)
		{
			GuiSkill* tmp = (GuiSkill*)element;
			if (tmp->skill_parents.size() == 0)
			{
				if (tmp->skill)
				{
					if(tmp->skill->UnlockSkill())
						tmp->image.SetTextureRect(tmp->unlocked);
				}
			}
			else
			{
				for (int i = 0; i < tmp->skill_parents.size(); i++)
				{
					if (tmp->skill_parents[i] && tmp->skill_parents[i]->unlocked)
					{
						if (tmp->skill)
						{
							if (tmp->skill->UnlockSkill())
							{
								tmp->image.SetTextureRect(tmp->unlocked);
								break;
							}
						}
					}
	
				}
			}
		}
		
		else if (even == EVENT_MOUSE_ENTER)
		{
			GuiSkill* tmp = (GuiSkill*)element;
				if (tmp->text)
					tmp->text->Activate();
			
		}
		
		else if (even == EVENT_MOUSE_EXIT)
		{
			GuiSkill* tmp = (GuiSkill*)element;
				if (tmp->text)
					tmp->text->Desactivate();
		}
		
	}

	/*
	//Blood spells delete button
	if (blooddeletebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			blooddeletebutton->SetTextureRect({ 324, 192, 38, 38 });
			skillpoints = skillpoints + fireballpoints + projectilespoints + manpoints + cogpoints + heartjawpoints;
			fireballpoints = projectilespoints = manpoints = cogpoints = heartjawpoints = 0;

			fireball_pressed = projectiles_pressed = man_pressed = cog_pressed = heartjaw_pressed = false;
			fireball->SetTextureRect({ 439, 920, 48, 48 });
			projectiles->SetTextureRect({ 488, 920, 48, 48 });
			man->SetTextureRect({ 537, 920, 48, 48 });
			cog->SetTextureRect({ 586, 920, 48, 48 });
			heartjaw->SetTextureRect({ 635, 920, 48, 48 });
		}
		break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			blooddeletebutton->SetTextureRect({ 285, 192, 38, 38 });
		}
		break;
		}
	}

	//Blood spells delete button
	if (nightdeletebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			nightdeletebutton->SetTextureRect({ 324, 192, 38, 38 });
			skillpoints = skillpoints + batwingpoints + wolfpoints + fangspoints + bigjawpoints + bloodmanpoints;
			batwingpoints = wolfpoints = fangspoints = bigjawpoints = bloodmanpoints = 0;

			batwing_pressed = wolf_pressed = fangs_pressed = bigjaw_pressed = bloodman_pressed = false;
			batwing->SetTextureRect({ 439, 969, 48, 48 });
			wolf->SetTextureRect({ 488, 969, 48, 48 });
			fangs->SetTextureRect({ 537, 969, 48, 48 });
			bigjaw->SetTextureRect({ 586, 969, 48, 48 });
			bloodman->SetTextureRect({ 635, 969, 48, 48 });
		}
		break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			nightdeletebutton->SetTextureRect({ 285, 192, 38, 38 });
		}
		break;
		}
	}


	//Martial blood -----------------------------------------------------------------------------------
	//Lion
	if (lion == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (lion_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				lionpoints++;
				lion_pressed = true;
				lion->SetTextureRect({ 341, 724, 48, 48 });
			}
			else if (lion_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				lionpoints++;
			}
			else if (lion_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				lionpoints = lionpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (star_pressed == true)
			{
				break;
			}
			if (lion_pressed == true)
			{
				lionpoints--;
				skillpoints++;

				if (lionpoints == 0)
				{
					lion_pressed = false;
					lion->SetTextureRect({ 439, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Claw
	if (claw == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (claw_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				clawpoints++;
				claw_pressed = true;
				claw->SetTextureRect({ 390, 724, 48, 48 });
			}
			else if (claw_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				clawpoints++;
			}
			else if (claw_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				clawpoints = clawpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (hand_pressed == true)
			{
				break;
			}
			else if (claw_pressed == true)
			{
				clawpoints--;
				skillpoints++;

				if (clawpoints == 0)
				{
					claw_pressed = false;
					claw->SetTextureRect({ 488, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Swords
	if (swords == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (swords_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				swordspoints++;
				swords_pressed = true;
				swords->SetTextureRect({ 341, 773, 48, 48 });
			}
			else if (swords_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				swordspoints++;
			}
			else if (swords_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				swordspoints = swordspoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (swords_pressed == true)
			{
				swordspoints--;
				skillpoints++;

				if (swordspoints == 0)
				{
					swords_pressed = false;
					swords->SetTextureRect({ 537, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Hand
	if (hand == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (claw_pressed == false)
			{
				break;
			}
			else if (hand_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				handpoints++;
				hand_pressed = true;
				hand->SetTextureRect({ 390, 773, 48, 48 });
			}
			else if (hand_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				handpoints++;
			}
			else if (hand_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				handpoints = handpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (hand_pressed == true)
			{
				handpoints--;
				skillpoints++;

				if (handpoints == 0)
				{
					hand_pressed = false;
					hand->SetTextureRect({ 586, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Star
	if (star == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (lion_pressed == false)
			{
				break;
			}
			else if (star_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				starpoints++;
				star_pressed = true;
				star->SetTextureRect({ 341, 822, 48, 48 });
			}
			else if (star_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				starpoints++;
			}
			else if (star_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				starpoints = starpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (star_pressed == true)
			{
				starpoints--;
				skillpoints++;

				if (starpoints == 0)
				{
					star_pressed = false;
					star->SetTextureRect({ 635, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}
	
	//Blood spells -----------------------------------------------------------------------------------
	//Fireball
	if (fireball == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (fireball_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				fireballpoints++;
				fireball_pressed = true;
				fireball->SetTextureRect({ 390, 822, 48, 48 });
			}
			else if (fireball_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				fireballpoints++;
			}
			else if (fireball_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				fireballpoints = fireballpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (cog_pressed == true || (heartjaw_pressed == true && projectiles_pressed == false))
			{
				break;
			}
			else if (fireball_pressed == true)
			{
				fireballpoints--;
				skillpoints++;

				if (fireballpoints == 0)
				{
					fireball_pressed = false;
					fireball->SetTextureRect({ 439, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Projectiles
	if (projectiles == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (projectiles_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				projectilespoints++;
				projectiles_pressed = true;
				projectiles->SetTextureRect({ 341, 871, 48, 48 });
			}
			else if (projectiles_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				projectilespoints++;
			}
			else if (projectiles_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				projectilespoints = projectilespoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (heartjaw_pressed == true && fireball_pressed == false)
			{
				break;
			}
			else if (projectiles_pressed == true)
			{
				projectilespoints--;
				skillpoints++;

				if (projectilespoints == 0)
				{
					projectiles_pressed = false;
					projectiles->SetTextureRect({ 488, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Man
	if (man == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (man_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				manpoints++;
				man_pressed = true;
				man->SetTextureRect({ 390, 871, 48, 48 });
			}
			else if (man_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				manpoints++;
			}
			else if (man_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				manpoints = manpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (man_pressed == true)
			{
				manpoints--;
				skillpoints++;

				if (manpoints == 0)
				{
					man_pressed = false;
					man->SetTextureRect({ 537, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Cog
	if (cog == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (fireball_pressed == false)
			{
				break;
			}
			else if (cog_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				cogpoints++;
				cog_pressed = true;
				cog->SetTextureRect({ 341, 920, 48, 48 });
			}
			else if (cog_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				cogpoints++;
			}
			else if (cog_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				cogpoints = cogpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (cog_pressed == true)
			{
				cogpoints--;
				skillpoints++;

				if (cogpoints == 0)
				{
					cog_pressed = false;
					cog->SetTextureRect({ 586, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Heartjaw
	if (heartjaw == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (fireball_pressed == false && projectiles_pressed == false)
			{
				break;
			}
			else if (heartjaw_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				heartjawpoints++;
				heartjaw_pressed = true;
				heartjaw->SetTextureRect({ 390, 920, 48, 48 });
			}
			else if (heartjaw_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				heartjawpoints++;
			}
			else if (heartjaw_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				heartjawpoints = heartjawpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (heartjaw_pressed == true)
			{
				heartjawpoints--;
				skillpoints++;

				if (heartjawpoints == 0)
				{
					heartjaw_pressed = false;
					heartjaw->SetTextureRect({ 635, 920, 48, 48 });
				}
			}
		}
		break;
		
		}
	}

	//Night summoning -----------------------------------------------------------------------------------
	//Batwing
	if (batwing == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (batwing_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				batwingpoints++;
				batwing_pressed = true;
				batwing->SetTextureRect({ 341, 969, 48, 48 });
			}
			else if (batwing_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				batwingpoints++;
			}
			else if (batwing_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				batwingpoints = batwingpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (bigjaw_pressed == true)
			{
				break;
			}
			if (batwing_pressed == true)
			{
				batwingpoints--;
				skillpoints++;

				if (batwingpoints == 0)
				{
					batwing_pressed = false;
					batwing->SetTextureRect({ 439, 969, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Wolf
	if (wolf == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (wolf_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				wolfpoints++;
				wolf_pressed = true;
				wolf->SetTextureRect({ 390, 969, 48, 48 });
			}
			else if (wolf_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				wolfpoints++;
			}
			else if (wolf_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				wolfpoints = wolfpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (bloodman_pressed == true && bigjaw_pressed == false)
			{
				break;
			}
			if (wolf_pressed == true)
			{
				wolfpoints--;
				skillpoints++;

				if (wolfpoints == 0)
				{
					wolf_pressed = false;
					wolf->SetTextureRect({ 488, 969, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Fangs
	if (fangs == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (fangs_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				fangspoints++;
				fangs_pressed = true;
				fangs->SetTextureRect({ 341, 1018, 48, 48 });
			}
			else if (fangs_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				fangspoints++;
			}
			else if (fangs_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				fangspoints = fangspoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (fangs_pressed == true)
			{
				fangspoints--;
				skillpoints++;

				if (fangspoints == 0)
				{
					fangs_pressed = false;
					fangs->SetTextureRect({ 537, 969, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Bigjaw
	if (bigjaw == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (batwing_pressed == false)
			{
				break;
			}
			else if (bigjaw_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				bigjawpoints++;
				bigjaw_pressed = true;
				bigjaw->SetTextureRect({ 390, 1018, 48, 48 });
			}
			else if (bigjaw_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				bigjawpoints++;
			}
			else if (bigjaw_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				bigjawpoints = bigjawpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (bloodman_pressed == true && wolf_pressed == false)
			{
				break;
			}
			if (bigjaw_pressed == true)
			{
				bigjawpoints--;
				skillpoints++;

				if (bigjawpoints == 0)
				{
					bigjaw_pressed = false;
					bigjaw->SetTextureRect({ 586, 969, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Bloodman
	if (bloodman == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (bigjaw_pressed == false && wolf_pressed == false)
			{
				break;
			}
			else if (bloodman_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				bloodmanpoints++;
				bloodman_pressed = true;
				bloodman->SetTextureRect({ 439, 1018, 48, 48 });
			}
			else if (bloodman_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				bloodmanpoints++;
			}
			else if (bloodman_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				bloodmanpoints = bloodmanpoints;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (bloodman_pressed == true)
			{
				bloodmanpoints--;
				skillpoints++;

				if (bloodmanpoints == 0)
				{
					bloodman_pressed = false;
					bloodman->SetTextureRect({ 635, 969, 48, 48 });
				}
			}
		}
		break;

		}
	}*/
}