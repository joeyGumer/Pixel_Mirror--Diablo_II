#include "j1App.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "hudSkilltree.h"


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

	skillpoints = 15;
	lionpoints = clawpoints = swordspoints = handpoints = starpoints = fireballpoints = projectilespoints = manpoints = cogpoints = heartjawpoints = batwingpoints = wolfpoints = fangspoints = bigjawpoints = bloodmanpoints = 0;
	

	//Night summoning ---------------------------------------------------------------------------
	nightsummoning = App->gui->AddGuiImage({ 321, 216 }, { 1449, 588, 320, 216 }, NULL, this);
	nightsummoning->active = false;
	hud_gui_elements.push_back(nightsummoning);

	bloodbutton = App->gui->AddGuiImage({ 230, 0 }, { 1678, 588, 90, 108 }, nightsummoning, this);
	bloodbutton->active = false;
	hud_gui_elements.push_back(bloodbutton);

	batwing = App->gui->AddGuiImage({ 82, 9 }, { 439, 969, 48, 48 }, nightsummoning, this);
	batwing->active = false;
	hud_gui_elements.push_back(batwing);

	wolf = App->gui->AddGuiImage({ 152, 9 }, { 488, 969, 48, 48 }, nightsummoning, this);
	wolf->active = false;
	hud_gui_elements.push_back(wolf);

	fangs = App->gui->AddGuiImage({ 15, 77 }, { 537, 969, 48, 48 }, nightsummoning, this);
	fangs->active = false;
	hud_gui_elements.push_back(fangs);

	bigjaw = App->gui->AddGuiImage({ 0, 68 }, { 586, 969, 48, 48 }, batwing, this);
	bigjaw->active = false;
	hud_gui_elements.push_back(bigjaw);

	bloodman = App->gui->AddGuiImage({ 0, 136 }, { 635, 969, 48, 48 }, wolf, this);
	bloodman->active = false;
	hud_gui_elements.push_back(bloodman);

	nightdeletebutton = App->gui->AddGuiImage({ 20, 165 }, { 285, 192, 38, 38 }, nightsummoning, this);
	nightdeletebutton->active = false;
	hud_gui_elements.push_back(nightdeletebutton);
	//--------------------------------------------------------------------------------------------


	//Martial blood ---------------------------------------------------------------------------
	martialblood = App->gui->AddGuiImage({ 321, 0 }, { 807, 434, 320, 216 }, NULL, this);
	martialblood->active = false;
	hud_gui_elements.push_back(martialblood);

	skillpoints_label = App->gui->AddGuiLabel("0", NULL, { 265, 62 }, martialblood, FONT_WHITE, this);
	skillpoints_label->active = false;
	hud_gui_elements.push_back(skillpoints_label);

	lion = App->gui->AddGuiImage({ 84, 14 }, { 439, 871, 48, 48 }, martialblood, this);
	lion->active = false;
	hud_gui_elements.push_back(lion);

	claw = App->gui->AddGuiImage({ 154, 14 }, { 488, 871, 48, 48 }, martialblood, this);
	claw->active = false;
	hud_gui_elements.push_back(claw);

	swords = App->gui->AddGuiImage({ 15, 82 }, { 537, 871, 48, 48 }, martialblood, this);
	swords->active = false;
	hud_gui_elements.push_back(swords);

	hand = App->gui->AddGuiImage({ 0, 68 }, { 586, 871, 48, 48 }, claw, this);
	hand->active = false;
	hud_gui_elements.push_back(hand);

	star = App->gui->AddGuiImage({ 0, 136 }, { 635, 871, 48, 48 }, lion, this);
	star->active = false;
	hud_gui_elements.push_back(star);

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

	fireball = App->gui->AddGuiImage({ 14, 16 }, { 439, 920, 48, 48 }, bloodspells, this);
	fireball->active = false;
	hud_gui_elements.push_back(fireball);

	projectiles = App->gui->AddGuiImage({ 84, 16 }, { 488, 920, 48, 48 }, bloodspells, this);
	projectiles->active = false;
	hud_gui_elements.push_back(projectiles);

	man = App->gui->AddGuiImage({ 152, 70 }, { 537, 920, 48, 48 }, bloodspells, this);
	man->active = false;
	hud_gui_elements.push_back(man);

	cog = App->gui->AddGuiImage({ 0, 121 }, { 586, 920, 48, 48 }, fireball, this);
	cog->active = false;
	hud_gui_elements.push_back(cog);

	heartjaw = App->gui->AddGuiImage({ 0, 121 }, { 635, 920, 48, 48 }, projectiles, this);
	heartjaw->active = false;
	hud_gui_elements.push_back(heartjaw);

	blooddeletebutton = App->gui->AddGuiImage({ 167, 165 }, { 285, 192, 38, 38 }, bloodspells, this);
	blooddeletebutton->active = false;
	hud_gui_elements.push_back(blooddeletebutton);
	
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
	text.create("%i", skillpoints);
	skillpoints_label->SetText(text);

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
		}
		break;
		}
	}

	//Blood spells button
	if (bloodbutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			nightsummoning->Desactivate();
			bloodspells->Activate();
		}
		break;
		}
	}

	//Martial delete button
	if (martialdeletebutton == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			martialdeletebutton->SetTextureRect({324, 192, 38, 38});
			skillpoints = skillpoints + lionpoints + clawpoints + swordspoints + handpoints + starpoints;
			lionpoints = clawpoints = swordspoints = handpoints = starpoints = 0;

			lion_pressed = claw_pressed = swords_pressed = hand_pressed = star_pressed = false;
			lion->SetTextureRect({ 439, 871, 48, 48 });
			claw->SetTextureRect({ 488, 871, 48, 48 });
			swords->SetTextureRect({ 537, 871, 48, 48 });
			hand->SetTextureRect({ 586, 871, 48, 48 });
			star->SetTextureRect({ 635, 871, 48, 48 });
		}
		break;

		case EVENT_MOUSE_LEFTCLICK_UP:
		{
			martialdeletebutton->SetTextureRect({ 285, 192, 38, 38 });
		}
		break;
		}
	}

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
	}
}