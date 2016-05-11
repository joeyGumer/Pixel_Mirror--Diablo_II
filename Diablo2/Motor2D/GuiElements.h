#ifndef __GUIELEMENTS_H__
#define __GUIELEMENTS_H__

#include "j1Module.h"
#include "p2Point.h"

#include <list>
;
using namespace std;
// WARNING: I'm doing trap here...
#include "SDL/include/SDL.h"

struct SDL_Texture;
struct _TTF_Font;
enum TextColor;
enum GUI_Type
{
	GUI_LABEL,
	GUI_IMAGE,
	GUI_BUTTON,
	GUI_INPUTBOX,
	GUI_SLIDER,
	GUI_MOUSE_IMAGE,
	GUI_ITEM,
	GUI_INVENTORY,
	GUI_SLOT,
	GUI_SKILL,
	GUI_MINIMAP,
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
	EVENT_ITEM_OUT,
	EVENT_ITEM_IN,
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
	bool CheckEvent(GuiElement* hover, GuiElement* focus, bool& interaction);
	void DrawDebug();
	void Center(bool x, bool y);

	//Activate and desactivate
	//NOTE: a bit useles...
	void Desactivate();
	void Activate();
	void ActivateChilds();
	void DesactivateChilds();
	//
	//Getters
	iPoint GetLocalPosition();
	iPoint GetScreenPosition();
	SDL_Rect GetScreenRect();
	SDL_Rect GetLocalRect();
	SDL_Rect GetTextureRect(){ return tex_rect; };
	
	void SetLocalPosition(iPoint p);
	void SetSize(int w, int h){ local_rect.w = w, local_rect.h = h; }
	void SetTextureRect(SDL_Rect r){ tex_rect = r; }
	void SetLocalRect(SDL_Rect r){ local_rect = r; }
	void SetLabel(GuiElement* label);
	void AddChild(GuiElement* child);
	void RemoveChild(GuiElement* child);

public:
	//not used
	GUI_Type	 type;
	//int		 id;
	GuiElement*  parent;
	GuiElement* descriptionlabel;
	list<GuiElement*> childs;
	//not defined
	bool         debug = false;
	bool		 active = true;
	bool         visible = true;
	bool		 interactable = false;
	bool		 draggable = false;
	bool		 focusable = false;
	bool		 mouseIn;
	bool		 focusIn;
	bool		 mask;
	j1Module*    listener;
	SDL_Rect     tex_rect;
	SDL_Color color;
private:
	SDL_Rect     local_rect;
	//For now we'll just use one listener
	//p2List<j1Module*> listeners;
};

class GuiLabel : public GuiElement
{
public:
	//TODO: Manage the font size
	GuiLabel(p2SString t, _TTF_Font* f, iPoint p, SDL_Color color, GuiElement* par, j1Module* list ,SDL_Color backgroundColor = { 0, 0, 0, 0 } );
	~GuiLabel(){}

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);

	//Utils
	void SetText(p2SString t);

public:
	p2SString text;
	_TTF_Font* font;
	SDL_Texture* tex;
	SDL_Color rectColor;
	
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

class GuiButton : public GuiElement
{
public:
	GuiButton(iPoint p, SDL_Rect idle_r1, SDL_Rect hover_r1, SDL_Rect click_r1, p2SString t, _TTF_Font* f, j1Module* list = NULL, GuiElement* parent = NULL);
	~GuiButton(){}

	void Draw();
	void Update(GuiElement* hover, GuiElement* focus);

public:
	GuiImage button_image;
	GuiLabel button_label;
	SDL_Rect idle_tex;
	SDL_Rect hover_tex;
	SDL_Rect click_tex;

};

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
//MOUSE
class GuiMouseImage : public GuiElement
{
public:
	GuiMouseImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list = NULL);
	~GuiMouseImage(){}

	void Draw();
	void Update();

public:
	GuiImage mouse_image;
	int mouse_y, mouse_x;

};
//----
#endif _GUIELEMENTS_H_