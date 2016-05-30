#ifndef __j1INPUT_H__
#define __j1INPUT_H__

#include "j1Module.h"
#include "p2Point.h"
#include <queue>

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

struct SDL_Rect;

enum j1EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum j1KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class j1Input : public j1Module
{

public:

	j1Input();

	// Destructor
	virtual ~j1Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Gather relevant win events
	bool GetWindowEvent(j1EventWindow ev);

	void StartInput(p2SString edit_input, int pos);
	void StopInput();
	p2SString GetInput(int& cursor);

	// Check key states (includes mouse and joy buttons)
	j1KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	j1KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	//Added for big utility
	
	//Gets the world coordinates of the mouse positionb 
	//NOTE : used because there where problems with the map movement
	iPoint GetMouseWorldPosition();

	//Gets the screen coordinates of the mouse position
	iPoint GetMousePosition();
	void GetMousePosition(int &x, int &y);
	
	iPoint GetMouseMotion();
	void GetMouseMotion(int& x, int& y);

private:
	bool		windowEvents[WE_COUNT];
	j1KeyState*	keyboard;
	j1KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;

	bool		enable_input;
	p2SString   input_text;
	int			cursor_pos;

public:
	std::queue<const char*>		down_queue;
	std::queue<const char*>		up_queue;
	std::queue<const char*>		repeat_queue;
};

#endif // __j1INPUT_H__