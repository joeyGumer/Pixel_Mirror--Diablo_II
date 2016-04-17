#include "GuiItem.h"
#include "j1App.h"
#include "j1Input.h"
#include "GuiSlot.h"
#include "GuiInventory.h"
#include "j1Gui.h"
#include "j1Render.h"



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
	delete[] coords;
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
			
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				inventory->FreeItem(this);
			}
		}
	}

	//If this is the dragging item, move it
	/*if (App->gui->dragged_item == this)
	{
		Move();
	}*/
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
	//TODO 4: Fill Move() function so, the item movement is exactly like the cursor (hint: not using the draggable property or mouse motion)
	//and also make that the item is centered at the cursor (is at the middle not at the vertex)
	iPoint tmp = App->input->GetMousePosition();
	tmp.x -= GetLocalRect().w / 2;
	tmp.y -= GetLocalRect().h / 2;

	SetLocalPosition(tmp);
}
