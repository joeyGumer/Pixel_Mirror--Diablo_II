#ifndef _GUIINVENTORY_H_
#define _GUIINVENTORY_H_

#include "GuiElements.h"
#include "p2Point.h"
#include "GuiSlot.h"
#include "GuiItem.h"
#include <vector>
#include <list>

using namespace std;
enum ITEM_TYPE;


class GuiInventory : public GuiElement
{
	/*
	-------Methods
	*/
public:

	//Constructor
	GuiInventory(iPoint p, SDL_Rect r, int columns, int rows, int slot_w, int slot_h, GuiElement* par = NULL, j1Module* list = NULL);

	//Destructor
	~GuiInventory();

	//Called each loop iteration
	void Update(GuiElement* hover, GuiElement* focus);

	//Blit to screen
	void Draw();
	
	//Draws debug elements
	void DrawDebug();
	
	//Deletes all items (only for this prototype)
	void CleanItems();

	/*
	//Coordinates sistem conversion functions:
	*/

	//From slot coordinate to local position in the inventory
	iPoint SlotToInventory(iPoint pos);

	//From local position in the inventory to the slot coordinate
	iPoint InventoryToSlot(iPoint pos);

	//From a screen point to the slot coordinate
	iPoint ScreenToSlot(iPoint pos);

	//Returns a pointer to the slot giving it's coord in the inventory
	GuiSlot* GetSlotFromCoord(iPoint& coord);

	//Returns the Coord that the item would have if placed on the inventory;
	iPoint	GetCoordFromItem(GuiItem* item);

	//Checks if the coord exists in the inventory space
	bool CoordExist(iPoint& coord);

	//---------

	/*
	//Assignation functions
	*/

	//Checks if there's space for an item
	bool IsPlaceable(GuiItem* item, iPoint& coord, bool exchange = false, GuiItem** extra_item = NULL);
	
	//Adds item to the inventory
	void AddItem(GuiItem* item, GuiSlot* new_slot);

	//Frees and Item from the inventory
	void FreeItem(GuiItem* item);

	//Places an item in exchange of another
	void Exchange(GuiItem* item1, GuiSlot* enter_slot, GuiItem* item2);

	//Checks if there's space for an item and then adds it
	bool AutomaticAddItem(GuiItem* item);

	//Checks the activy of the dragged item over the inventory
	void CheckDraggedItem(GuiItem* drag_item);

	//Asigns the item to the group of slots that it will occupy
	void AssignItemToSlots(GuiItem* item, iPoint& coord);

	//--------
	
	//Slot coloring, because of feedback :D
	void SetSlotsState(GuiItem* item, SLOT_STATE state);
	
	/*
	--------Attributes
	*/
private:
	
	int columns;
	int rows;
	int slot_width;
	int slot_height;

	GuiImage image;
	
	//Vector of slots (vector and no list because the vector navigation is a lot faster, and it will be used a lot)
	vector<GuiSlot> slots;

public:

	//List of items (list and not a vector, because if there are more than one inventory, the items will be spliced)
	list<GuiItem*> items;
	ITEM_TYPE restriction;
};

#endif _GUIINVENTORY_H_