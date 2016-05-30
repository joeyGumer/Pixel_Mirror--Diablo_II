#include "hudBelt.h"
#include "j1App.h"
#include "j1Gui.h"
//NOPE
#include "j1Game.h"
#include "j1HUD.h"
#include "j1Player.h"
#include "j1Input.h"
#include "Skill.h"
#include "PlayerSkills.h"
#include "j1Audio.h"
//NOTE: PROVISIONAL 
#include "j1Fonts.h"

#include "Item.h"
#include "j1InputManager.h"

//Constructor
hudBelt::hudBelt():hudElement()
{
	active = true;
}

//Destructor
hudBelt::~hudBelt()
{}

//Called before fist frame
bool hudBelt::Start()
{
	//Player
	player = App->game->player;
	potionfx = App->audio->LoadFx("audio/fx/Potion3.ogg");
	//
	life_current_h = mana_current_h = 78;

	HUD = App->gui->AddGuiImage({ 166, 431 }, { 166, 386, 408, 47 }, NULL, this);
	hud_gui_elements.push_back(HUD);

	HUDornament = App->gui->AddGuiImage({ 96, -5 }, { 262, 381, 115, 5 }, HUD, this);
	hud_gui_elements.push_back(HUDornament);

	inventory1 = App->gui->AddGuiInventory({ 176, 9 }, { 342, 395, 30, 30 }, 1, 1 , 30, 30, HUD, this);
	inventory1->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory1);
	inventory2 = App->gui->AddGuiInventory({ 207, 9 }, { 373, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory2->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory2);
	inventory3 = App->gui->AddGuiInventory({ 238, 9 }, { 404, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory3->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory3);
	inventory4 = App->gui->AddGuiInventory({ 269, 9 }, { 435, 395, 30, 30 }, 1, 1, 30, 30, HUD, this);
	inventory4->restriction = ITEM_CONSUMABLE;
	hud_gui_elements.push_back(inventory4);
	//HUD elements definition
	//NOTE: these position are very inaccurate

	HUDback1 = App->gui->AddGuiImage({ -132, -19 }, { 362, 226, 76, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback1);
	
	HUDback2 = App->gui->AddGuiImage({ 364, -18 }, { 437, 226, 80, 53 }, HUD, this);
	hud_gui_elements.push_back(HUDback2);

	life = App->gui->AddGuiImage({ -136, -44 }, { 371, 118, 79, 78 }, HUD, this);
	hud_gui_elements.push_back(life);



	mana = App->gui->AddGuiImage({ 365, -44 }, { 451, 118, 78, 78 }, HUD, this);
	hud_gui_elements.push_back(mana);

	

	stamina = App->gui->AddGuiImage({ 27, 20 }, { 530, 118, 102, 18 }, HUD, this);
	hud_gui_elements.push_back(stamina);

	life_holder = App->gui->AddGuiImage({ -166, -55 }, { 0, 331, 116, 103 }, HUD, this);
	hud_gui_elements.push_back(life_holder);

	life_label = App->gui->AddGuiLabel("50/50", App->font->description, { 0, -10 }, life_holder, FONT_WHITE, this);
	hud_gui_elements.push_back(life_label);
	life_label->Center(true, false);

	mana_holder = App->gui->AddGuiImage({ 358, -55 }, { 524, 331, 116, 102 }, HUD, this);
	hud_gui_elements.push_back(mana_holder);

	mana_label = App->gui->AddGuiLabel("50/50", App->font->description, { 0, -10 }, mana_holder, FONT_WHITE, this);
	hud_gui_elements.push_back(mana_label);
	mana_label->Center(true, false);

	/*
	runbutton = App->gui->AddGuiImage({ 9, 19 }, { 153, 280, 18, 22 }, HUD, this);
	runbutton->interactable = true;
	hud_gui_elements.push_back(runbutton);
	*/
	runbutton = App->gui->AddGuiImageWithLabel({ 9, 19 }, { 153, 280, 18, 22 }, "run (R)", App->font->description, { -10, -10 }, HUD, this);
	runbutton->interactable = true;
	hud_gui_elements.push_back(runbutton);

	/*
	minipanelbutton = App->gui->AddGuiImage({ 146, 9 }, { 296, 253, 16, 27 }, HUD, this);
	minipanelbutton->interactable = true;
	hud_gui_elements.push_back(minipanelbutton);
	*/

	//Skills
	attack_left = App->gui->AddGuiSkill({ -50, 0 }, { 51, 280, 50, 47 }, { 102, 280, 50, 47 }, player->right_skill, HUD, this);
	hud_gui_elements.push_back(attack_left);

	attack_right = App->gui->AddGuiSkill({ 308, 0 }, { 51, 280, 50, 47 }, { 102, 280, 50, 47 }, player->left_skill, HUD, this);
	hud_gui_elements.push_back(attack_right);

	//Left Skills
	//Attack 1 ----------------------------------------
	left_basic_attack = App->gui->AddGuiSkill({ 0, -47 }, { 51, 280, 50, 47 }, { 102, 280, 50, 47 }, player->basic_attack, attack_left, this);
	left_basic_attack->active = false;
	hud_gui_elements.push_back(left_basic_attack);

	//Martial Blood
	left_stinging_strike = App->gui->AddGuiSkill({ 0, -94 }, { 735, 871, 50, 47 }, { 1499, 805, 50, 47 }, player->stinging_strike, attack_left, this);
	left_stinging_strike->active = false;
	hud_gui_elements.push_back(left_stinging_strike);


	left_wild_talon = App->gui->AddGuiSkill({ 50, -94 }, { 684, 871, 50, 47 }, { 1448, 805, 50, 47 }, player->wild_talon, attack_left, this);
	left_wild_talon->active = false;
	hud_gui_elements.push_back(left_wild_talon);

	left_bat_strike = App->gui->AddGuiSkill({ 100, -94 }, { 837, 871, 50, 47 }, { 1601, 805, 50, 47 }, player->bat_strike, attack_left, this);
	left_bat_strike->active = false;
	hud_gui_elements.push_back(left_bat_strike);

	left_soul_of_ice = App->gui->AddGuiSkill({ 150, -94 }, { 888, 871, 50, 47 }, { 1652, 805, 50, 47 }, player->soul_of_ice, attack_left, this);
	left_soul_of_ice->active = false;
	hud_gui_elements.push_back(left_soul_of_ice);

	//Right Skills
	right_basic_attack = App->gui->AddGuiSkill({ 0, -47 }, { 51, 280, 50, 47 }, { 102, 280, 50, 47 }, player->basic_attack, attack_right, this);
	right_basic_attack->active = false;
	hud_gui_elements.push_back(right_basic_attack);

	//Martial Blood
	right_stinging_strike = App->gui->AddGuiSkill({ 0, -94 }, { 735, 871, 50, 47 }, { 1499, 805, 50, 47 }, player->stinging_strike, attack_right, this);
	right_stinging_strike->active = false;
	hud_gui_elements.push_back(right_stinging_strike);

	right_wild_talon = App->gui->AddGuiSkill({ -50, -94 }, { 684, 871, 50, 47 }, { 1448, 805, 50, 47 }, player->wild_talon, attack_right, this);
	right_wild_talon->active = false;
	hud_gui_elements.push_back(right_wild_talon);

	right_bat_strike = App->gui->AddGuiSkill({ -100, -94 }, { 837, 871, 50, 47 }, { 1601, 805, 50, 47 }, player->bat_strike, attack_right, this);
	right_bat_strike->active = false;
	hud_gui_elements.push_back(right_bat_strike);

	right_soul_of_ice = App->gui->AddGuiSkill({ -150, -94 }, { 888, 871, 50, 47 }, { 1652, 805, 50, 47 }, player->soul_of_ice, attack_right, this);
	right_soul_of_ice->active = false;
	hud_gui_elements.push_back(right_soul_of_ice);

	krobus_arts = App->gui->AddGuiSkill({ -50, -47 }, { 786, 871, 50, 47 }, { 1550, 805, 50, 47 }, player->krobus_arts, attack_right, this);
	krobus_arts->active = false;
	hud_gui_elements.push_back(krobus_arts);

	//Blood spells
	blood_arrow = App->gui->AddGuiSkill({ 0, -141 }, { 684, 920, 50, 47 }, { 1448, 854, 50, 47 }, player->blood_arrow, attack_right, this);
	blood_arrow->active = false;
	hud_gui_elements.push_back(blood_arrow);

	vampire_breath = App->gui->AddGuiSkill({ -50, -141 }, { 735, 920, 50, 47 }, { 1499, 854, 50, 47 }, player->vampire_breath, attack_right, this);
	vampire_breath->active = false;
	hud_gui_elements.push_back(vampire_breath);

	blood_bomb = App->gui->AddGuiSkill({ -100, -141 }, { 837, 920, 50, 47 }, { 1601, 854, 50, 47 }, player->blood_bomb, attack_right, this);
	blood_bomb->active = false;
	hud_gui_elements.push_back(blood_bomb);

	red_feast = App->gui->AddGuiSkill({ -150, -141 }, { 888, 920, 50, 47 }, { 1652, 854, 50, 47 }, player->red_feast, attack_right, this);
	red_feast->active = false;
	hud_gui_elements.push_back(red_feast);

	heard_of_bats = App->gui->AddGuiSkill({ 0, -188 }, { 684, 969, 50, 47 }, { 1449, 903, 50, 47 }, player->heard_of_bats, attack_right, this);
	heard_of_bats->active = false;
	hud_gui_elements.push_back(heard_of_bats);

	shadow_walker = App->gui->AddGuiSkill({ -100, -47 }, { 735, 969, 50, 47 }, { 1499, 903, 50, 47 }, player->shadow_walker, attack_right, this);
	shadow_walker->active = false;
	hud_gui_elements.push_back(shadow_walker);

	clotted_blood = App->gui->AddGuiSkill({ -150, -47 }, { 888, 969, 50, 47 }, { 1652, 903, 50, 47 }, player->clotted_blood, attack_right, this);
	clotted_blood->active = false;
	hud_gui_elements.push_back(clotted_blood);
	


	/*skill12 = App->gui->AddGuiImage({ 20, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill12->interactable = true;
	skill12->active = false;
	hud_gui_elements.push_back(skill12);

	skill13 = App->gui->AddGuiImage({ 91, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill13->interactable = true;
	skill13->active = false;
	hud_gui_elements.push_back(skill13);

	//Attack 2 ----------------------------------------
	skill21 = App->gui->AddGuiImage({ 305, -70 }, { 51, 280, 50, 47 }, HUD, this);
	skill21->interactable = true;
	skill21->active = false;
	hud_gui_elements.push_back(skill21);

	skill22 = App->gui->AddGuiImage({ 233, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill22->interactable = true;
	skill22->active = false;
	hud_gui_elements.push_back(skill22);

	skill23 = App->gui->AddGuiImage({ 162, -70 }, { 0, 280, 50, 47 }, HUD, this);
	skill23->interactable = true;
	skill23->active = false;
	hud_gui_elements.push_back(skill23);*/

	//Minipanel's buttons -------------------------------
	
	minipanel = App->gui->AddGuiImage({ 98, -25 }, { 170, 253, 110, 25 }, HUD, this);
	hud_gui_elements.push_back(minipanel);

	/*stats = App->gui->AddGuiImage({ 3, 3 }, { 170, 279, 20, 19 }, minipanel, this);
	stats->interactable = true;
	hud_gui_elements.push_back(stats);*/

	stats = App->gui->AddGuiImageWithLabel({ 3, 3 }, { 170, 279, 20, 19 }, "player (C)", App->font->description, { -30, 0 }, minipanel, this);
	stats->interactable = true;
	hud_gui_elements.push_back(stats);

	inventorybutton = App->gui->AddGuiImageWithLabel({ 24, 3 }, { 191, 279, 20, 19 }, "invenTory (I)", App->font->description, {-30, 0}, minipanel, this);
	inventorybutton->interactable = true;
	hud_gui_elements.push_back(inventorybutton);

	skilltree = App->gui->AddGuiImageWithLabel({ 45, 3 }, { 212, 279, 20, 19 }, "skill Tree (S)", App->font->description, {-30, 0}, minipanel, this);
	skilltree->interactable = true;
	hud_gui_elements.push_back(skilltree);

	minimapbutton = App->gui->AddGuiImageWithLabel({ 66, 3 }, { 233, 279, 20, 19 }, "mini map (TAB)", App->font->description, { -40, 0 }, minipanel, this);
	minimapbutton->interactable = true;
	hud_gui_elements.push_back(minimapbutton);

	game_menu = App->gui->AddGuiImageWithLabel({ 87, 3 }, { 254, 279, 20, 19 }, "game menu (ESC)", App->font->description, {-30, 0}, minipanel, this);
	game_menu->interactable = true;
	hud_gui_elements.push_back(game_menu);
	
	minipanelbutton = App->gui->AddGuiImageWithLabel({ 146, 9 }, { 296, 253, 14, 25 }, "open/close minipanel", App->font->description, { -60, 0 }, HUD, this);
	minipanelbutton->interactable = true;
	hud_gui_elements.push_back(minipanelbutton);

	minipanel->Desactivate();

	return true;
}

//Called before each loop iteration
bool hudBelt::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		RunningOn();
	}

	list<ShortCut*>::iterator it = App->im->shortcuts_list.begin();

	while (it != App->im->shortcuts_list.end())
	{
		if ((*it)->name == "Potion 1" && (*it)->active)
		{
			list<GuiItem*>::iterator it = inventory1->items.begin();
			if (it != inventory1->items.end())
			{
				App->audio->PlayFx(potionfx);
				GuiItem* i = (*it);
				i->nexus->Effect();
				i->FreeSlots();
				inventory1->items.remove(i);
				RELEASE(i);
			}
		}

		if ((*it)->name == "Potion 2" && (*it)->active)
		{
			list<GuiItem*>::iterator it = inventory2->items.begin();
			if (it != inventory2->items.end())
			{
				App->audio->PlayFx(potionfx);
				GuiItem* i = (*it);
				i->nexus->Effect();
				i->FreeSlots();
				inventory2->items.remove(i);
				RELEASE(i);
			}
		}

		if ((*it)->name == "Potion 3" && (*it)->active)
		{
			list<GuiItem*>::iterator it = inventory3->items.begin();
			if (it != inventory3->items.end())
			{
				App->audio->PlayFx(potionfx);
				GuiItem* i = (*it);
				i->nexus->Effect();
				i->FreeSlots();
				inventory3->items.remove(i);
				RELEASE(i);
			}
		}

		if ((*it)->name == "Potion 4" && (*it)->active)
		{
			list<GuiItem*>::iterator it = inventory4->items.begin();
			if (it != inventory4->items.end())
			{
				App->audio->PlayFx(potionfx);
				GuiItem* i = (*it);
				i->nexus->Effect();
				i->FreeSlots();
				inventory4->items.remove(i);
				RELEASE(i);
			}
		}

		++it;
	}

	//NOTE: doing this each frame but... meh, whatever
	//AAAAAND i have the rects inverted, yay
	if (attack_right->skill->avaliable)
	{
		attack_right->image.SetTextureRect(attack_right->locked);
	}
	else
	{
		attack_right->image.SetTextureRect(attack_right->unlocked);
	}

	if (attack_left->skill->avaliable)
	{
		attack_left->image.SetTextureRect(attack_left->locked);
	}
	else
	{
		attack_left->image.SetTextureRect(attack_left->unlocked);
	}

	return true;
}

//Called each frame
bool hudBelt::Update(float dt)
{
	return true;
}

//Called after each loop iteration
bool hudBelt::PostUpdate()
{
	return true;
}

//Called before quitting
bool hudBelt::CleanUp()
{

	//NOTE: the problems between lists and vectors begin to grow, but i think this is a good way to approach this
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

//Called when there's a gui event
void hudBelt::OnEvent(GuiElement* element, GUI_Event even)
{
	//HUD -------------------------------------
	//Run button
	if (runbutton == element)
	{
		switch (even)
		{
			case EVENT_MOUSE_LEFTCLICK_DOWN:
			{
				RunningOn();
			}
			break;
			case EVENT_MOUSE_ENTER:
			{
				runbutton->descriptionlabel->Activate();
			}
			break;
			case EVENT_MOUSE_EXIT:
			{
				runbutton->descriptionlabel->Desactivate();
			}
			break;
		}
	}
	//Mini panel button
	else if (minipanelbutton == element)
	{
		switch (even)
		{
			case EVENT_MOUSE_LEFTCLICK_DOWN:
			{
				if (minipanel_pressed == false)
				{
					HUDornament->Desactivate();
					minipanel_pressed = true;
					minipanelbutton->SetTextureRect({ 281, 253, 14, 25 });
					minipanel->Activate();
				}
				else
				{
					HUDornament->Activate();
					minipanel_pressed = false;
					minipanelbutton->SetTextureRect({ 296, 253, 14, 25 });
					minipanel->Desactivate();
				}
			}
			break;
			case EVENT_MOUSE_ENTER:
			{
				minipanelbutton->descriptionlabel->Activate();
			}
			break;
			case EVENT_MOUSE_EXIT:
			{
				minipanelbutton->descriptionlabel->Desactivate();
			}
			break;
		}
	}
	
	//Inventory button
	else if (inventorybutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (inventorybutton_pressed == false)
			{
				inventorybutton_pressed = true;
			}
			else
			{
				inventorybutton_pressed = false;
			}
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			inventorybutton->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			inventorybutton->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//Stats button
	else if (stats == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (statsbutton_pressed == false)
			{
				 statsbutton_pressed = true;
			}
			else
			{
				statsbutton_pressed = false;
			}
		}
			break;
		case EVENT_MOUSE_ENTER:
		{
			stats->descriptionlabel->Activate();
		}
			break;
		case EVENT_MOUSE_EXIT:
		{
			stats->descriptionlabel->Desactivate();
		}
			break;
		}
	}

	//Skilltree button
	else if (skilltree == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skilltreebutton_pressed == false)
				skilltreebutton_pressed = true;
			else
				skilltreebutton_pressed = false;
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			skilltree->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			skilltree->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//MiniMap button
	else if (minimapbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (minimapbutton_pressed == false)
			{
				minimapbutton_pressed = true;
			}
			else
			{
				minimapbutton_pressed = false;
			}
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			minimapbutton->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			minimapbutton->descriptionlabel->Desactivate();
		}
		break;
		}
	}
	//Game_menu button
	else if (game_menu == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (menubutton_pressed == false)
				menubutton_pressed = true;
			else
				menubutton_pressed = false;
		}
		break;
		case EVENT_MOUSE_ENTER:
		{
			game_menu->descriptionlabel->Activate();
		}
		break;
		case EVENT_MOUSE_EXIT:
		{
			game_menu->descriptionlabel->Desactivate();
		}
		break;
		}
	}

	//Attack1
	else if (attack_right == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (attack1_pressed == false)
			{
				attack1_pressed = true;
				list<GuiElement*>::iterator it = attack_right->childs.begin();
				for (; it != attack_right->childs.end(); it++)
				{
					if (((GuiSkill*)(*it))->skill->unlocked)
					{
						(*it)->active = true;
					}
				}
			}
			else
			{
				attack1_pressed = false;
				attack_right->DesactivateChilds();
			}
		}
		break;
		}
	}

	//Attack2
	else if (attack_left == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (attack2_pressed == false)
			{
				attack2_pressed = true;
				list<GuiElement*>::iterator it = attack_left->childs.begin();
				for (; it != attack_left->childs.end(); it++)
				{
					if (((GuiSkill*)(*it))->skill->unlocked)
					{
						(*it)->active = true;
					}
				}

			}
			else
			{
				attack2_pressed = false;
				attack_left->DesactivateChilds();
			}
		}
		break;
		}
	}

	else if (attack1_pressed)
	{
		list<GuiElement*>::iterator it = attack_right->childs.begin();
		for (; it != attack_right->childs.end(); it++)
		{
			if (element == (*it))
			{
				if (even == EVENT_MOUSE_LEFTCLICK_DOWN)
				{
					attack_right->skill = ((GuiSkill*)element)->skill;
					attack_right->image.SetTextureRect(((GuiSkill*)element)->image.GetTextureRect());
					attack_right->unlocked = ((GuiSkill*)element)->unlocked;
					attack_right->locked = ((GuiSkill*)element)->locked;
					player->right_skill = attack_right->skill;
					//NOTE: If you don't like this delete it
					//--
					attack1_pressed = false;
					attack_right->DesactivateChilds();
					//--
					break;
				}
			}
		}
	}
	else if (attack2_pressed)
	{
		list<GuiElement*>::iterator it = attack_left->childs.begin();
		for (; it != attack_left->childs.end(); it++)
		{
			if (element == (*it))
			{
				if (even == EVENT_MOUSE_LEFTCLICK_DOWN)
				{
					attack_left->skill = ((GuiSkill*)element)->skill;
					attack_left->image.SetTextureRect(((GuiSkill*)element)->image.GetTextureRect());
					attack_left->unlocked = ((GuiSkill*)element)->unlocked;
					attack_left->locked = ((GuiSkill*)element)->locked;
					player->left_skill = attack_left->skill;
					//NOTE: If you don't like this delete it
					//--
					attack2_pressed = false;
					attack_left->DesactivateChilds();
					//--
					break;
				}
			}
		}
	}


	
}

//Sets the life stat at the HUD
void hudBelt::SetLife(int max_HP, int HP)
{
	p2SString text;
	text.create("%i / %i",HP, max_HP);
	life_label->SetText(text);
	life_label->Center(true, false);

	if (HP != max_HP && HP != 0)
	{
		life_current_h = STAT_MAX_H / max_HP;
		life_current_h *= HP;
	}
	else if (max_HP == HP)
	{
		life_current_h = STAT_MAX_H;
	}
	else if (HP == 0)
	{
		life_current_h = 0;
	}

	/*if (App->debug)
	{
	life_debug->SetText(("%d / %d", HP, max_HP));
	}*/

	life->SetTextureRect({ 371, STAT_TEX_Y - int(life_current_h), 79, int(life_current_h) });
	life->SetLocalPosition({ -136, STAT_LOCAL_Y - int(life_current_h) });
}

//Sets the mana stat at the HUD
void hudBelt::SetMana(int max_MP, int MP)
{
	p2SString text;
	text.create("%i / %i", MP, max_MP);
	mana_label->SetText(text);
	mana_label->Center(true, false);
	
	if (MP != max_MP && MP != 0)
	{
		mana_current_h = STAT_MAX_H / max_MP;
		mana_current_h *= MP;
	}
	else if (max_MP == MP)
	{
		mana_current_h = STAT_MAX_H;
	}
	else if (MP == 0)
	{
		mana_current_h = 0;
	}
	
	/*if (App->debug)
	{
	mana_debug->SetText("FUCK YOU");
	}*/

	mana->SetTextureRect({ 451, STAT_TEX_Y - int(mana_current_h), 78, int(mana_current_h) });
	mana->SetLocalPosition({ 365, STAT_LOCAL_Y - int(mana_current_h) });
}

void hudBelt::SetStamina(int max_ST, int ST)
{
	if (ST != max_ST && ST != 0)
	{
		stamina_current_w = STAT_MAX_W / max_ST;
		stamina_current_w *= ST;
	}
	else if (max_ST == ST)
	{
		stamina_current_w = STAT_MAX_W;
	}
	else if (ST == 0)
	{
		stamina_current_w = 0;
	}

	stamina->SetTextureRect({ 530, 118, int(stamina_current_w), 18 });
}

void hudBelt::RunningOn()
{
	bool run = player->RunOn();

	if (run)
	{
		runbutton->SetTextureRect({ 153, 301, 18, 22 });
	}
	else
	{
		runbutton->SetTextureRect({ 153, 280, 18, 22 });
	}
}

//NOTE: not sure but meh
void hudBelt::UnlockSkill()
{
	
}