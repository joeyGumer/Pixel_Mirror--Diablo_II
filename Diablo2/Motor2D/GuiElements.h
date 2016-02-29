#ifndef __GUIELEMENTS_H__
#define __GUIELEMENTS_H__

#include "j1Module.h"
#include "p2Point.h"
//I'm doing trap here...
#include "SDL/include/SDL.h"

struct SDL_Texture;
struct _TTF_Font;

enum GUI_Type
{
	GUI_LABEL,
	GUI_IMAGE,
	GUI_BUTTON,
	GUI_INPUTBOX,
	GUI_SLIDER,
};

enum GUI_Event
{
	EVENT_MOUSE_LEFTCLICK_DOWN,
	EVENT_MOUSE_LEFTCLICK_UP,
	EVENT_MOUSE_RIGHTCLICK_DOWN,
	EVENT_MOUSE_RIGHTCLICK_UP,
	EVENT_MOUSE_ENTER,
	EVENT_MOUSE_EXIT,
	EVENT_FOCUS_DOWN,
	EVENT_FOCUS_UP,
	EVENT_INPUT_CHANGE,
	EVENT_SLIDER_CHANGE,
};

class GuiElement
{
public:
	GuiElement(iPoint p, GUI_Type t, GuiElement* par, j1Module* list);
	GuiElement(iPoint p, SDL_Rect r, GUI_Type t, GuiElement* par, j1Module* list);
	~GuiElement(){}

	virtual void Draw(){}
	virtual void Update(GuiElement* hover, GuiElement* focus){}

	//Utils
	bool CheckCollision(iPoint p);
	bool CheckEvent(GuiElement* hover, GuiElement* focus);
	void DrawDebug();
	void Center(bool x, bool y);

	//Utils
	iPoint GetLocalPosition();
	iPoint GetScreenPosition();
	SDL_Rect GetScreenRect();
	SDL_Rect GetLocalRect();
	
	void SetLocalPosition(iPoint p);
	void SetSize(int w, int h){ local_rect.w = w, local_rect.h = h; }
	void SetTextureRect(SDL_Rect r){ tex_rect = r; }
	void SetLocalRect(SDL_Rect r){ local_rect = r; }


public:
	//not used
	GUI_Type	 type;
	//int		 id;
	GuiElement*  parent;
	//not defined
	bool         visible;
	bool		 mouseIn;
	bool		 interactable;
	bool		 draggable;
	bool		 focusable;
	bool		 focusIn;
	bool		 mask;
	j1Module*    listener;
	SDL_Rect     tex_rect;

private:
	SDL_Rect     local_rect;
	//For now we'll just use one listener
	//p2List<j1Module*> listeners;
};

class GuiLabel : public GuiElement
{
public:
	//TODO: Manage the font size
	GuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list);
	~GuiLabel(){}

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);

	//Utils
	void SetText(p2SString t);

public:
	p2SString text;
	_TTF_Font* font;
	SDL_Texture* tex;
};

class GuiImage : public GuiElement
{
public:
	GuiImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list);
	~GuiImage(){};

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);
};

class GuiInputBox : public GuiElement
{
public:

	GuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list);
	~GuiInputBox(){};


	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);
	//Utils
	bool Input();

public:
	GuiLabel text;
	GuiImage image;

	bool	inputOn;
	bool	init;
	bool	password;
	iPoint	cursor;
	int		cursor_pos;
};


//EXERCISE 1
class GuiSlider : public GuiElement
{
public:
	GuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int width, int thumb_h ,iPoint offset, float value, GuiElement* par, j1Module* list);
	~GuiSlider(){};

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);
	
	//EXERCISE 5
	float GetValue()const;
public:
	GuiImage image;
	GuiImage thumb;

	float	max_value;
	int		width;
	int     thumb_pos;
	bool	clicking = false;
};
//----
#endif _GUIELEMENTS_H_