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

	skillpoints = 10;
	skill1points = skill2points = skill3points = skill4points = skill5points = skill6points = skill7points = skill8points = skill9points = skill10points = 0;

	skilltree = App->gui->AddGuiImage({ 321, 0 }, { 807, 434, 319, 432 }, NULL, this);
	skilltree->active = false;
	hud_gui_elements.push_back(skilltree);

	skill1 = App->gui->AddGuiImage({84, 14}, { 439, 871, 48, 48 }, skilltree, this);
	skill1->active = false;
	hud_gui_elements.push_back(skill1);

	skill2 = App->gui->AddGuiImage({ 15, 82 }, { 488, 871, 48, 48 }, skilltree, this);
	skill2->active = false;
	hud_gui_elements.push_back(skill2);

	skill3 = App->gui->AddGuiImage({ 69, 68 }, { 439, 920, 48, 48 }, skill1, this);
	skill3->active = false;
	hud_gui_elements.push_back(skill3);

	skill4 = App->gui->AddGuiImage({ 0, 136 }, { 488, 920, 48, 48 }, skill1, this);
	skill4->active = false;
	hud_gui_elements.push_back(skill4);

	skill5 = App->gui->AddGuiImage({ 0, 68 }, { 537, 871, 48, 48 }, skill3, this);
	skill5->active = false;
	hud_gui_elements.push_back(skill5);

	skill6 = App->gui->AddGuiImage({ 0, 136 }, { 586, 871, 48, 48 }, skill2, this);
	skill6->active = false;
	hud_gui_elements.push_back(skill6);

	skill7 = App->gui->AddGuiImage({ 0, 68 }, { 537, 920, 48, 48 }, skill4, this);
	skill7->active = false;
	hud_gui_elements.push_back(skill7);

	skill8 = App->gui->AddGuiImage({ 0, 137 }, { 586, 920, 48, 48 }, skill5, this);
	skill8->active = false;
	hud_gui_elements.push_back(skill8);

	skill9 = App->gui->AddGuiImage({ 0, 137 }, { 635, 871, 48, 48 }, skill6, this);
	skill9->active = false;
	hud_gui_elements.push_back(skill9);

	skill10 = App->gui->AddGuiImage({ 0, 137 }, { 635, 920, 48, 48 }, skill7, this);
	skill10->active = false;
	hud_gui_elements.push_back(skill10);
	
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
	//Skill1
	if (skill1 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill1_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill1points++;
				skill1_pressed = true;
				skill1->SetTextureRect({ 341, 724, 48, 48 });
			}
			else if (skill1_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill1points++;
			}
			else if (skill1_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill1points = skill1points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill3_pressed == true || skill4_pressed == true)
			{
				break;
			}
			if (skill1_pressed == true)
			{
				skill1points--;
				skillpoints++;

				if (skill1points == 0)
				{
					skill1_pressed = false;
					skill1->SetTextureRect({ 439, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill2
	if (skill2 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill2_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill2points++;
				skill2_pressed = true;
				skill2->SetTextureRect({ 390, 724, 48, 48 });
			}
			else if (skill2_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill2points++;
			}
			else if (skill2_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill2points = skill2points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill6_pressed == true)
			{
				break;
			}
			else if (skill2_pressed == true)
			{
				skill2points--;
				skillpoints++;

				if (skill2points == 0)
				{
					skill2_pressed = false;
					skill2->SetTextureRect({ 488, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill3
	if (skill3 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill1_pressed == false)
			{
				break;
			}
			else if (skill3_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill3points++;
				skill3_pressed = true;
				skill3->SetTextureRect({ 341, 773, 48, 48 });
			}
			else if (skill3_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill3points++;
			}
			else if (skill3_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill3points = skill3points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill5_pressed == true)
			{
				break;
			}
			else if (skill3_pressed == true)
			{
				skill3points--;
				skillpoints++;

				if (skill3points == 0)
				{
					skill3_pressed = false;
					skill3->SetTextureRect({ 439, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill4
	if (skill4 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill1_pressed == false)
			{
				break;
			}
			else if (skill4_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill4points++;
				skill4_pressed = true;
				skill4->SetTextureRect({ 390, 773, 48, 48 });
			}
			else if (skill4_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill4points++;
			}
			else if (skill4_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill4points = skill4points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill7_pressed == true)
			{
				break;
			}
			else if (skill4_pressed == true)
			{
				skill4points--;
				skillpoints++;

				if (skill4points == 0)
				{
					skill4_pressed = false;
					skill4->SetTextureRect({ 488, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill5
	if (skill5 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill3_pressed == false)
			{
				break;
			}
			else if (skill5_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill5points++;
				skill5_pressed = true;
				skill5->SetTextureRect({ 341, 822, 48, 48 });
			}
			else if (skill5_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill5points++;
			}
			else if (skill5_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill5points = skill5points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill8_pressed == true)
			{
				break;
			}
			else if (skill5_pressed == true)
			{
				skill5points--;
				skillpoints++;

				if (skill5points == 0)
				{
					skill5_pressed = false;
					skill5->SetTextureRect({ 537, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill6
	if (skill6 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill2_pressed == false)
			{
				break;
			}
			else if (skill6_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill6points++;
				skill6_pressed = true;
				skill6->SetTextureRect({ 390, 822, 48, 48 });
			}
			else if (skill6_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill6points++;
			}
			else if (skill6_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill6points = skill6points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill9_pressed == true)
			{
				break;
			}
			else if (skill6_pressed == true)
			{
				skill6points--;
				skillpoints++;

				if (skill6points == 0)
				{
					skill6_pressed = false;
					skill6->SetTextureRect({ 586, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill7
	if (skill7 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill4_pressed == false)
			{
				break;
			}
			else if (skill7_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill7points++;
				skill7_pressed = true;
				skill7->SetTextureRect({ 341, 871, 48, 48 });
			}
			else if (skill7_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill7points++;
			}
			else if (skill7_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill7points = skill7points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill10_pressed == true)
			{
				break;
			}
			else if (skill7_pressed == true)
			{
				skill7points--;
				skillpoints++;

				if (skill7points == 0)
				{
					skill7_pressed = false;
					skill7->SetTextureRect({ 537, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill8
	if (skill8 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill5_pressed == false)
			{
				break;
			}
			else if (skill8_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill8points++;
				skill8_pressed = true;
				skill8->SetTextureRect({ 390, 871, 48, 48 });
			}
			else if (skill8_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill8points++;
			}
			else if (skill8_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill8points = skill8points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill8_pressed == true)
			{
				skill8points--;
				skillpoints++;

				if (skill8points == 0)
				{
					skill8_pressed = false;
					skill8->SetTextureRect({ 586, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill9
	if (skill9 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill6_pressed == false)
			{
				break;
			}
			else if (skill9_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill9points++;
				skill9_pressed = true;
				skill9->SetTextureRect({ 341, 920, 48, 48 });
			}
			else if (skill9_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill9points++;
			}
			else if (skill9_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill9points = skill9points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill9_pressed == true)
			{
				skill9points--;
				skillpoints++;

				if (skill9points == 0)
				{
					skill9_pressed = false;
					skill9->SetTextureRect({ 635, 871, 48, 48 });
				}
			}
		}
		break;

		}
	}

	//Skill10
	if (skill10 == element)
	{
		switch (even)
		{
		case EVENT_MOUSE_LEFTCLICK_DOWN:
		{
			if (skill7_pressed == false)
			{
				break;
			}
			else if (skill10_pressed == false && skillpoints > 0)
			{
				skillpoints--;
				skill10points++;
				skill10_pressed = true;
				skill10->SetTextureRect({ 390, 920, 48, 48 });
			}
			else if (skill10_pressed == true && skillpoints > 0)
			{
				skillpoints--;
				skill10points++;
			}
			else if (skill10_pressed == true && skillpoints == 0)
			{
				skillpoints = skillpoints;
				skill10points = skill10points;
			}
		}
		break;

		case EVENT_MOUSE_RIGHTCLICK_DOWN:
		{
			if (skill10_pressed == true)
			{
				skill10points--;
				skillpoints++;

				if (skill10points == 0)
				{
					skill10_pressed = false;
					skill10->SetTextureRect({ 635, 920, 48, 48 });
				}
			}
		}
		break;

		}
	}

}