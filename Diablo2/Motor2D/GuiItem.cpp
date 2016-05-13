#include "GuiItem.h"
#include "j1App.h"
#include "j1Input.h"
#include "GuiSlot.h"
#include "GuiInventory.h"
#include "j1Gui.h"
#include "j1Render.h"
//Absolutely not
#include "j1Player.h"
#include "j1Game.h"
#include "Item.h"


GuiItem::GuiItem(int s, iPoint* coord, SDL_Rect r) 
	:GuiElement({ 0, 0 }, r, GUI_ITEM, NULL, NULL)
	, image({ 0, 0 }, r, this, NULL)
{
	size = s;
	coords = new iPoint[size];
	reference_slot = NULL;
	inventory = NULL;
	
	pivot = { ITEM_SECTION_SIZE / 2, ITEM_SECTION_SIZE / 2 };
	
	for (int i = 0; i < s; i++)
	{
		coords[i] = coord[i];
	}
}

GuiItem::~GuiItem()
{
	RELEASE(coords);
	RELEASE(text);
	if (!convert)
		RELEASE(nexus);
}

void GuiItem::Draw()
{
	image.Draw();
}

void GuiItem::DrawDebug()
{
	image.DrawDebug();

	iPoint tmp = GetPivotPosition();
	
	App->render->DrawQuad({ tmp.x, tmp.y, 2, 2 }, 0, 255, 0, 1000, true, false);

}

void GuiItem::Update(GuiElement* hover, GuiElement* focus)
{
	//If there's no dragged_item, when clicking over the item, it's freed from the inventory
	if (!(App->gui->dragged_item))
	{
		if (CheckCollision(App->input->GetMousePosition()))
		{
			//Feedback :D
			inventory->SetSlotsState(this, GREEN);

			mousehover = true;

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				inventory->FreeItem(this);

			}
		}
		else
			mousehover = false;
		
			
	}

	
	if (App->gui->dragged_item == this)
	{
		mousehover = false;
	}
}

//Gives the pivot position over the screen
iPoint GuiItem::GetPivotPosition()
{
	iPoint ret = pivot;
	ret += GetScreenPosition();

	return ret;
}

//Frees the slots under the item
void GuiItem::FreeSlots()
{
	//TODO 6: iterate all the slots that the item occupies and free them (inventory_item = NULL)
	//Hint: functionality very similiar to AssignItemToSlots(), but now at item.cpp, and freeing the slots
	for (int i = 0; i < size; i++)
	{
		GuiSlot* slot = inventory->GetSlotFromCoord(reference_slot->coords + coords[i]);
		if (slot)
			slot->inventory_item = NULL;
	}
}

//Moves accordingly to the mouse
void GuiItem::Move()
{ 
	iPoint tmp = App->input->GetMousePosition();
	tmp.x -= GetLocalRect().w / 2;
	tmp.y -= GetLocalRect().h / 2;

	SetLocalPosition(tmp);
}

//Moves accordingly to the mouse
void GuiItem::CreateText()
{
	
	attributeText.push_back(StringColor(nexus->name, nexus->rarity_color));
	//TEMPORAL
	
		
	for (int i =0 ; i < nexus->attribute_type.size(); i++)
	{
		SDL_Color color = FONT_WHITE;
		if (nexus->buff_value[i] < 0)
		{
			color = FONT_RED;
		}
		p2SString Text("%i", nexus->buff_value[i]);
		switch (nexus->attribute_type[i])
		{
			case STRENGHT:
				Text.Insert(0, "StrengTh :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case DEXTERITY:
				Text.Insert(0, "DEXTERITY :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case INTELLIGENCE:
				Text.Insert(0, "INTELLIGENCE :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case VITALITY:
				Text.Insert(0, "VITALITY :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case LUCK:
				Text.Insert(0, "LUCK :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case ARMOR:
				Text.Insert(0, "ARMOR :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case BLOOD:
				Text.Insert(0, "BLOOD :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case COOLDOWN:
				Text.Insert(0, "COOLDOWN REDUCTION:");
				attributeText.push_back(StringColor(Text, color));
				break;
			case POTION:
				Text.Insert(0, "POTION EFFECT :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case BLOOD_MAX:
				Text.Insert(0, "MAX BLOOD :");
				attributeText.push_back(StringColor(Text, color));
				break;
			case PURE_BLOOD:
				Text.Insert(0, "PURE BLOOD :");
				attributeText.push_back(StringColor(Text, color));
				break;
			}
	}
	

	
	text = new GuiText({ 0, 0 }, attributeText, this, NULL);
	text->Activate();
}