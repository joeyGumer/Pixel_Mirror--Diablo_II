#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "j1Module.h"
#include "p2Log.h"
#include "j1App.h"
//#include "j1UIManager.h"
#include "PugiXml\src\pugixml.hpp"
#include <queue>
#include "GuiElements.h"

enum INPUT_TYPE
{
	DOWN,
	UP,
	REPEAT
};

struct ShortCut
{
	ShortCut()
	{}

	ShortCut(INPUT_TYPE _type, string _name, string _command)
	{
		type = _type;
		name = _name;
		command = _command;
	}

	INPUT_TYPE	 type;
	bool		 active;
	bool		 ready_to_change = false;
	string		 name;
	string		 command;

	GuiLabel*	 command_label = nullptr;
	GuiLabel*	 shortcut_label = nullptr;
};

class j1InputManager : public j1Module
{
public:

	j1InputManager();

	// Destructor
	virtual ~j1InputManager();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//bool LoadShortcutsInfo();

	//Refresh commands once have been changed
	void ChangeShortcutCommand(ShortCut* shortcut);

public:
	//Shortcuts list
	list<ShortCut*>			shortcuts_list;

	//Shortcuts xml file path
	string					inputs_file_path;

	//Shortcuts UI management
	//GuiImage*				pop_up = nullptr;
	//void OnEvent(GuiElement* gui, GUI_Event even);
};

#endif // __INPUT_MANAGER_H__