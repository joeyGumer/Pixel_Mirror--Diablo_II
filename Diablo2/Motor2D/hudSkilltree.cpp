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
	p2SString text2;
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
	raise_wolf = App->gui->AddGuiSkill({ 152, 9 }, { 488, 969, 48, 48 }, { 390, 969, 48, 48 }, player->shadow_walker, nightsummoning, this);
	raise_wolf->active = false;
	hud_gui_elements.push_back(raise_wolf);
	skills.push_back(raise_wolf);
	
	price11 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, raise_wolf, FONT_WHITE, this);
	price11->active = false;
	hud_gui_elements.push_back(price11);
	
	bat_girl = App->gui->AddGuiSkill({ 15, 77 }, { 537, 969, 48, 48 }, { 341, 1018, 48, 48 }, player->night_ward, nightsummoning, this);
	bat_girl->active = false;
	hud_gui_elements.push_back(bat_girl);
	skills.push_back(bat_girl);

	raise_blood_hawk = App->gui->AddGuiSkill({ 82, 9 }, { 586, 969, 48, 48 }, { 390, 1018, 48, 48 }, player->lust, nightsummoning, this);
	raise_blood_hawk->active = false;
	hud_gui_elements.push_back(raise_blood_hawk);
	skills.push_back(raise_blood_hawk);

	blood_golem = App->gui->AddGuiSkill({ 82, 77 }, { 537, 920, 48, 48 }, { 390, 871, 48, 48 }, player->undead, nightsummoning, this);
	blood_golem->active = false;
	blood_golem->skill_parents.push_back(raise_blood_hawk->skill);
	hud_gui_elements.push_back(blood_golem);
	skills.push_back(blood_golem);

	clotted_blood_skin = App->gui->AddGuiSkill({ 152, 145 }, { 635, 969, 48, 48 }, { 439, 1018, 48, 48 }, player->clotted_blood, nightsummoning, this);
	clotted_blood_skin->active = false;
	clotted_blood_skin->skill_parents.push_back(blood_golem->skill);
	clotted_blood_skin->skill_parents.push_back(raise_wolf->skill);
	hud_gui_elements.push_back(clotted_blood_skin);
	skills.push_back(clotted_blood_skin);

	price12 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, clotted_blood_skin, FONT_WHITE, this);
	price12->active = false;
	hud_gui_elements.push_back(price12);

	price13 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, raise_blood_hawk, FONT_WHITE, this);
	price13->active = false;
	hud_gui_elements.push_back(price13);

	price14 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, bat_girl, FONT_WHITE, this);
	price14->active = false;
	hud_gui_elements.push_back(price14);

	price15 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, blood_golem, FONT_WHITE, this);
	price15->active = false;
	hud_gui_elements.push_back(price15);

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
	skills.push_back(clotted_blood_skin);

	wild_talon = App->gui->AddGuiSkill({ 84, 14 }, { 439, 871, 48, 48 }, { 341, 724, 48, 48 }, player->wild_talon, martialblood, this);
	wild_talon->active = false;
	hud_gui_elements.push_back(wild_talon);
	skills.push_back(wild_talon);

	bat_strike = App->gui->AddGuiSkill({ 154, 82 }, { 586, 871, 48, 48 }, { 390, 773, 48, 48 }, player->bat_strike, martialblood, this);
	bat_strike->active = false;
	bat_strike->skill_parents.push_back(stinging_strike->skill);
	hud_gui_elements.push_back(bat_strike);
	skills.push_back(bat_strike);
	
	soul_of_ice = App->gui->AddGuiSkill({ 84, 150 }, { 635, 871, 48, 48 }, { 341, 822, 48, 48 }, player->soul_of_ice, martialblood, this);
	soul_of_ice->active = false;
	soul_of_ice->skill_parents.push_back(wild_talon->skill);
	hud_gui_elements.push_back(soul_of_ice);
	skills.push_back(soul_of_ice);

	krobus_arts = App->gui->AddGuiSkill({ 15, 82 }, { 537, 871, 48, 48 }, { 341, 773, 48, 48 }, player->krobus_arts, martialblood, this);
	krobus_arts->active = false;
	hud_gui_elements.push_back(krobus_arts);
	skills.push_back(krobus_arts);

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
	skills.push_back(blood_arrow);

	vampire_breath = App->gui->AddGuiSkill({ 84, 16 }, { 488, 920, 48, 48 }, { 341, 871, 48, 48 }, player->vampire_breath, bloodspells, this);
	vampire_breath->active = false;
	hud_gui_elements.push_back(vampire_breath);
	skills.push_back(vampire_breath);

	blood_bomb = App->gui->AddGuiSkill({ 14, 138 }, { 586, 920, 48, 48 }, { 341, 920, 48, 48 }, player->blood_bomb, bloodspells, this);
	blood_bomb->active = false;
	blood_bomb->skill_parents.push_back(blood_arrow->skill);
	hud_gui_elements.push_back(blood_bomb);
	skills.push_back(blood_bomb);

	red_feast = App->gui->AddGuiSkill({ 83, 138 }, { 635, 920, 48, 48 }, { 390, 920, 48, 48 }, player->red_feast, bloodspells, this);
	red_feast->active = false;
	red_feast->skill_parents.push_back(blood_arrow->skill);
	red_feast->skill_parents.push_back(vampire_breath->skill);
	hud_gui_elements.push_back(red_feast);
	skills.push_back(red_feast);

	heard_of_bats = App->gui->AddGuiSkill({ 152, 70 }, { 439, 969, 48, 48 }, { 341, 969, 48, 48 }, player->heard_of_bats, bloodspells, this);
	heard_of_bats->active = false;
	hud_gui_elements.push_back(heard_of_bats);
	skills.push_back(heard_of_bats);
	

	//LEVELS (not prices) -------------------------------------------------------------------------------------------------------------------------
	
	price1 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, stinging_strike, FONT_WHITE, this);
	price1->active = false;
	hud_gui_elements.push_back(price1);

	price2 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, wild_talon, FONT_WHITE, this);
	price2->active = false;
	hud_gui_elements.push_back(price2);

	price3 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, bat_strike, FONT_WHITE, this);
	price3->active = false;
	hud_gui_elements.push_back(price3);

	price4 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, soul_of_ice, FONT_WHITE, this);
	price4->active = false;
	hud_gui_elements.push_back(price4);
	
	price5 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, krobus_arts, FONT_WHITE, this);
	price5->active = false;
	hud_gui_elements.push_back(price5);

	price6 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, blood_arrow, FONT_WHITE, this);
	price6->active = false;
	hud_gui_elements.push_back(price6);

	price7 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, vampire_breath, FONT_WHITE, this);
	price7->active = false;
	hud_gui_elements.push_back(price7);

	price8 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, blood_bomb, FONT_WHITE, this);
	price8->active = false;
	hud_gui_elements.push_back(price8);

	price9 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, red_feast, FONT_WHITE, this);
	price9->active = false;
	hud_gui_elements.push_back(price9);

	price10 = App->gui->AddGuiLabel("0", NULL, { 44, 43 }, heard_of_bats, FONT_WHITE, this);
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
	clotted_blood_skin->text = App->gui->AddGuiText({ -20, 0 }, clottedtext, clotted_blood_skin, this);
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
	batgirltext.push_back(StringColor("nighT ward", FONT_VIOLET));
	batgirltext.push_back(StringColor("Passive: afTer 5 seconds you geT a shield", FONT_WHITE));
	batgirltext.push_back(StringColor("ThaT absorbs an amounT of The damage Taken", FONT_WHITE));
	batgirltext.push_back(StringColor("when The shield is desTroyed, The passive", FONT_WHITE));
	batgirltext.push_back(StringColor("will be available again afTer 60 seconds", FONT_WHITE));
	text.create("%i", player->night_ward->price);
	text.Insert(0, "pure BLOOD COST: ");
	batgirltext.push_back(StringColor(text, FONT_YELLOW));
	batgirltext.push_back(StringColor("percenT of your life absorbed: 24", FONT_GREEN));
	/*
	text.create("%i", player->night_ward->damage_reduction_base);
	text.Insert(0, "percenT of your life absorbed: ");
	batgirltext.push_back(StringColor(text, FONT_GREEN));
	*/
	bat_girl->text = App->gui->AddGuiText({ 0, 0 }, batgirltext, bat_girl, this);
	bat_girl->Desactivate();
	texts.push_back(bat_girl->text);
	hud_gui_elements.push_back(bat_girl->text);
	batgirltext.clear();


	vector<StringColor> hawktext;
	hawktext.push_back(StringColor("lusT", FONT_VIOLET));
	hawktext.push_back(StringColor("Passive: basic aTTacks generaTes addiTional", FONT_WHITE));
	hawktext.push_back(StringColor("blood charges and increases The maximum life", FONT_WHITE));
	text.create("%i", player->lust->price);
	text.Insert(0, "pure BLOOD COST: ");
	hawktext.push_back(StringColor(text, FONT_YELLOW));
	text.create("%i", player->lust->basic_blood_charges);
	text.Insert(0, "blood charges per basic: ");
	hawktext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->lust->increased_HP);
	text.Insert(0, "maximum life: ");
	hawktext.push_back(StringColor(text, FONT_RED));
	raise_blood_hawk->text = App->gui->AddGuiText({ 0, 0 }, hawktext, raise_blood_hawk, this);
	raise_blood_hawk->Desactivate();
	texts.push_back(raise_blood_hawk->text);
	hud_gui_elements.push_back(raise_blood_hawk->text);
	hawktext.clear();


	vector<StringColor> golemtext;
	golemtext.push_back(StringColor("undead", FONT_VIOLET));
	golemtext.push_back(StringColor("Passive: if you are going To die, This passive", FONT_WHITE));
	golemtext.push_back(StringColor("makes you invulnerable, increases The damage", FONT_WHITE));
	golemtext.push_back(StringColor("and gives life per kill for 4 seconds", FONT_WHITE));
	golemtext.push_back(StringColor("The passive will be available again afTer 60 seconds", FONT_WHITE));
	golemtext.push_back(StringColor("pure blood cosT: 2500", FONT_YELLOW));
	/*
	text.create("%i", player->undead->price);
	text.Insert(0, "pure BLOOD COST: ");
	golemtext.push_back(StringColor(text, FONT_YELLOW));
	*/
	text.create("%i", player->undead->extra_damage);
	text.Insert(0, "exTra damage: ");
	golemtext.push_back(StringColor(text, FONT_GREEN));
	text.create("%i", player->undead->life_steal);
	text.Insert(0, "life per kill: ");
	golemtext.push_back(StringColor(text, FONT_RED));
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
	stinging_strike->text = App->gui->AddGuiText({ 0, 145 }, stingtext, stinging_strike, this);
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
	wild_talon->text = App->gui->AddGuiText({ 0, 145 }, talontext, wild_talon, this);
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
	text.create("%i", player->bat_strike->blood_charge_cost_base);
	text.Insert(0, "BLOOD charges cosT: ");
	battext.push_back(StringColor(text, FONT_PURPLE));
	text.create("%i", player->bat_strike->life_steal);
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
	bat_strike->text = App->gui->AddGuiText({ -20, 145 }, battext, bat_strike, this);
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
	krobus_arts->text = App->gui->AddGuiText({ 0,145 }, krobustext, krobus_arts, this);
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
	heard_of_bats->text = App->gui->AddGuiText({ -110, 0 }, herdtext, heard_of_bats, this);
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
	

	text.create("%i", player->stinging_strike->level + 1);
	price1->SetText(text);

	text.create("%i", player->wild_talon->level + 1);
	price2->SetText(text);

	text.create("%i", player->bat_strike->level + 1);
	price3->SetText(text);

	text.create("%i", player->soul_of_ice->level + 1);
	price4->SetText(text);

	text.create("%i", player->krobus_arts->level + 1);
	price5->SetText(text);

	text.create("%i", player->blood_arrow->level + 1);
	price6->SetText(text);

	text.create("%i", player->vampire_breath->level + 1);
	price7->SetText(text);

	text.create("%i", player->blood_bomb->level + 1);
	price8->SetText(text);

	text.create("%i", player->red_feast->level + 1);
	price9->SetText(text);

	text.create("%i", player->heard_of_bats->level + 1);
	price10->SetText(text);

	text.create("%i", player->shadow_walker->level + 1);
	price11->SetText(text);

	text.create("%i", player->clotted_blood->level + 1);
	price12->SetText(text);

	text.create("%i", player->lust->level + 1);
	price13->SetText(text);

	text.create("%i", player->night_ward->level + 1);
	price14->SetText(text);

	text.create("%i", player->undead->level + 1);
	price15->SetText(text);

	for (int i = 0; i < skills.size(); i++)
	{
		if (skills[i]->skill->unlocked)
		{
			skills[i]->image.tex_rect = skills[i]->unlocked;
		}
		else
		{
			skills[i]->image.tex_rect = skills[i]->locked;
		}
	}
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
	skills.clear();

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
}