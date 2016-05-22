#include "GuiElements.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Textures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )



/*
--------Constructors
*/

//May i change this in the future for the rect
GuiElement::GuiElement(iPoint p, GUI_Type t, GuiElement* par = NULL, j1Module* list = NULL) : type(t), parent(par), listener(list), mouseIn(false)
{
	local_rect = { p.x, p.y, tex_rect.w, tex_rect.h };
	interactable = false;
	focusable = false;
	draggable = false;
	mask = true;
}

GuiElement::GuiElement(iPoint p, SDL_Rect r, GUI_Type t, GuiElement* par, j1Module* list) 
	: parent(par), tex_rect(r), type(t), listener(list), mouseIn(false)
{
	local_rect = { p.x, p.y, tex_rect.w, tex_rect.h };
	interactable = false;
	focusable = false;
	draggable = false;
	mask = false;
}

GuiLabel::GuiLabel(p2SString t, _TTF_Font* f, iPoint p, SDL_Color color, GuiElement* par, j1Module* list = NULL, SDL_Color backgroundColor)
	: GuiElement(p, GUI_LABEL, par, list), text(t), font(f)
{
	// NOTE :Have to polish the texture sistem in the label
	tex = App->font->Print(text.GetString(),color,f);
	this->color = color;
	rectColor = backgroundColor;
	tex_rect = { 0, 0, 0, 0 };
	App->font->CalcSize(text.GetString(), tex_rect.w, tex_rect.h,f);
	SetLocalRect({ p.x, p.y, tex_rect.w, tex_rect.h});
}


GuiImage::GuiImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list = NULL) 
	: GuiElement(p, r, GUI_IMAGE, par, list)
{}

GuiImage::GuiImage(iPoint p, SDL_Rect r, SDL_Texture* tex, GuiElement* par, j1Module* list)
	: GuiElement(p, r, GUI_IMAGE, par, list)
{
	outside_tex = tex;
}

//NOTE :I'm doing an especific constructor, have to change this
GuiInputBox::GuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
	: GuiElement(p, r, GUI_INPUTBOX, par, list), text(t, f, { 0, 0 },FONT_WHITE, this), image({ offset.x, offset.y }, r, this)
{
	SetLocalRect({ p.x, p.y, width, text.GetLocalRect().h});
	
	image.Center(true, true);
	inputOn = false;
	init = false;
	password = false;
	cursor_pos = 0;

	App->font->CalcSize("A", cursor.x, cursor.y);
	cursor.x = 0;
}

GuiButton::GuiButton(iPoint p, SDL_Rect idle_r1, SDL_Rect hover_r1, SDL_Rect click_r1, p2SString t, _TTF_Font* f, j1Module* list, GuiElement* parent)
	: GuiElement(p, idle_r1, GUI_BUTTON, parent, list),
	  button_image(p, idle_r1, this, NULL),
	  button_label(t, f, p,FONT_BLACK, this, NULL)
{
	button_image.Center(true, true);
	button_label.Center(true, true);

	interactable = true;

	idle_tex = idle_r1;
	hover_tex = hover_r1;
	click_tex = click_r1;
}

GuiMouseImage::GuiMouseImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list)
	: GuiElement(p, r, GUI_MOUSE_IMAGE, par, list), mouse_image({ p.x, p.y }, r, this, NULL)
{}

GuiAnimation::GuiAnimation(iPoint p, Animation anim, SDL_Texture* texture, GuiElement* par, j1Module* list)
		: GuiElement(p, GUI_ANIM, par, list)
{
	anima = anim;
	tex = texture;
}



GuiText::GuiText(iPoint p, vector<StringColor> text, GuiElement* par, j1Module* list)
	: GuiElement(p, GUI_TEXT,par, list)
{
	tex_rect.w = 0;
	int y = 0;
	for (int i = 0; i < text.size(); i++)
	{
		if (i >= 1)
			y += labels[0].tex_rect.h;
		
		
		labels.push_back(GuiLabel(text[i].string.GetString(), App->font->description, { p.x ,y}, text[i].color, this, list));
		if (labels[i].tex_rect.w > tex_rect.w)
			tex_rect.w = labels[i].tex_rect.w;
	}
	
	if (text.size() > 0)
		tex_rect.h = labels[0].tex_rect.h * text.size();
	SetLocalRect({ GetLocalRect().x, GetLocalRect().y, tex_rect.w, tex_rect.h});
	
	Center(true, false);
	for (int i = 0; i < text.size(); i++)
	{
		labels[i].Center(true, false);
	}

	p.x = GetLocalPosition().x + p.x;
	p.y = GetLocalPosition().y - tex_rect.h;
	SetLocalPosition(p);
	interactable = false;

}
//-----

//Draw functions
//MOUSE----------------------------
void GuiMouseImage::Draw()
{
	iPoint p = GetScreenPosition();

	App->render->Blit(App->gui->GetAtlas(),
		p.x - App->render->camera.x,
		p.y - App->render->camera.y,
		&tex_rect);
}
//---------------------------------
void GuiImage::Draw()
{
	iPoint p = GetScreenPosition();
	
	if (!outside_tex)
	{
		App->render->Blit(App->gui->GetAtlas(),
			p.x - App->render->camera.x,
			p.y - App->render->camera.y,
			&tex_rect);
	}
	else
	{
		App->render->Blit(outside_tex,
			p.x - App->render->camera.x,
			p.y - App->render->camera.y,
			&tex_rect);
	}
}

void GuiLabel::Draw()
{
	if (rectColor.a != 0)
	{
		App->render->DrawQuad({ (GetScreenPosition().x - App->render->camera.x), (GetScreenPosition().y - App->render->camera.y), tex_rect.w , tex_rect.h }, rectColor.r, rectColor.g, rectColor.b, rectColor.a);
	}
	App->render->Blit(tex, GetScreenPosition().x - App->render->camera.x, GetScreenPosition().y - App->render->camera.y, NULL);	
}

void GuiInputBox::Draw()
{
	image.Draw();
	text.Draw();

	if (inputOn)
	{
		iPoint pos = GetScreenPosition();
		App->render->DrawQuad({ pos.x + cursor.x - App->render->camera.x, pos.y - App->render->camera.y, CURSOR_WIDTH, cursor.y }, 255, 255, 255);
	}
}

void GuiButton::Draw()
{
	button_image.Draw();
	button_label.Draw();
}
void GuiText::Draw()
{
	App->render->DrawQuad({ (GetScreenPosition().x - App->render->camera.x), (GetScreenPosition().y - App->render->camera.y), tex_rect.w, tex_rect.h }, 0, 0, 0, 225);
	for (int i = 0; i < labels.size(); i++)
	{
		labels[i].Draw();
	}
}

void GuiAnimation::Draw()
{
	App->render->Blit(tex, (GetScreenPosition().x - App->render->camera.x), (GetScreenPosition().y - App->render->camera.y), &anima.GetCurrentFrame());
}

void GuiText::SetText(int index, p2SString t)
{
	labels[index].SetText(t);
}


//

//Update functions
//MOUSE-----------------
void GuiMouseImage::Update()
{
	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
	
	this->SetLocalPosition({ mouse_x, mouse_y });
}
//----------------------
void GuiImage::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}

void GuiLabel::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}
void GuiAnimation::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}
void GuiInputBox::Update(GuiElement* hover, GuiElement* focus)
{
	bool focused = (focus == this);
	
	if (!init && focused)
	{
		text.SetText("");
		init = true;
	}

	if (inputOn != focused)
	{
		if (focused)
			App->input->StartInput(text.text, cursor_pos);
		else
			App->input->StopInput();

		inputOn = focused;
	}


	if (inputOn)
	{
		int changed_cursor;
		p2SString added_text = App->input->GetInput(changed_cursor);
		
		if (added_text != text.text || changed_cursor != cursor_pos)
		{
			if (added_text != text.text)
			{
				text.SetText(added_text);
				if (listener)
					listener->OnEvent(this, EVENT_INPUT_CHANGE);
			}


			cursor_pos = changed_cursor;
			if (cursor_pos > 0)
			{
				
				p2SString selection(100);
				selection.Reserve(added_text.Length() * 2);
			
				added_text.SubString(0, cursor_pos, selection);
				
				App->font->CalcSize(selection.GetString(), cursor.x, cursor.y);
			}
			else
			{
				cursor.x = 0;
			}
		}
	}

}

void GuiButton::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}
void GuiText::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}
//GuiLabel Functions
void GuiLabel::SetText(p2SString t)
{
	if (tex)
		SDL_DestroyTexture(tex);

	text = t.GetString();
	tex = App->font->Print(text.GetString(),color,font);
	
	uint w, h;
	App->tex->GetSize(tex, w, h);
	SetSize(w, h);
}

//GuiElement Functions
iPoint GuiElement::GetLocalPosition()
{
	return{ local_rect.x, local_rect.y };
}

iPoint GuiElement::GetScreenPosition()
{
	if (parent)
	{
		iPoint ret;
		ret.x = local_rect.x + parent->GetScreenPosition().x;
		ret.y = local_rect.y + parent->GetScreenPosition().y;
		return ret;
	}

	return{ local_rect.x, local_rect.y };
}

void GuiElement::SetLabel(GuiElement* label)
{
	descriptionlabel = label;
	descriptionlabel->Desactivate();
}
SDL_Rect GuiElement::GetScreenRect()
{
	return{ GetScreenPosition().x, GetScreenPosition().y, local_rect.w, local_rect.h };
}
SDL_Rect GuiElement::GetLocalRect()
{
	return local_rect;
}

void GuiElement::SetLocalPosition(iPoint p)
{
	local_rect.x = p.x;
	local_rect.y = p.y;
}

void GuiElement::Center(bool x, bool y)
{
	if (x || y)
	{
		int fw, fh;
		if (parent)
		{
			fw = parent->GetLocalRect().w;
			fh = parent->GetLocalRect().h;
		}
		else
		{
			fw = App->render->camera.w;
			fh = App->render->camera.h;
		}
		int w, h;
		SDL_Rect rect = GetLocalRect();
		if (x)
			w = fw / 2 - rect.w / 2;
		else
			w = rect.x;

		if (y)
			h = fh / 2 - rect.h / 2;
		else
			h = rect.y;

		SetLocalPosition({ w, h });
	}
}

bool GuiElement::CheckCollision(iPoint p)
{
	bool ret = false;
	if (p.x >  GetScreenPosition().x &&
		p.x < (GetScreenPosition().x + local_rect.w) &&
		p.y >  GetScreenPosition().y &&
		p.y < (GetScreenPosition().y + local_rect.h))
	{
		ret = true;
	}
	return ret;
}

bool GuiElement::CheckEvent(GuiElement* hover, GuiElement* focus, bool& interaction)
{
	bool inside = (hover == this);
	bool focused = (focus == this);
	

		if (inside != mouseIn)
		{
			if (listener)
			{
				if (inside)
				{
					listener->OnEvent(this, EVENT_MOUSE_ENTER);
				}
				else
					listener->OnEvent(this, EVENT_MOUSE_EXIT);
			}
			mouseIn = inside;
		}
		
		if (inside)
		{
			if (type !=  GUI_MINIMAP)
				interaction = true;

			if (listener)
			{
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
					listener->OnEvent(this, EVENT_MOUSE_LEFTCLICK_DOWN);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
					listener->OnEvent(this, EVENT_MOUSE_LEFTCLICK_UP);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
					listener->OnEvent(this, EVENT_MOUSE_RIGHTCLICK_DOWN);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
					listener->OnEvent(this, EVENT_MOUSE_RIGHTCLICK_UP);
			}

			if (draggable && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				iPoint p = GetLocalPosition();
				iPoint m = App->input->GetMouseMotion();
				SetLocalPosition(p + m);
			}
		}

		if (focusIn != focused)
		{
			if (listener)
			{
				if (focused)
					listener->OnEvent(this, EVENT_FOCUS_DOWN);
				else
					listener->OnEvent(this, EVENT_FOCUS_UP);
			}
			focusIn = focused;
		}

		if (focused)
		{
			if (listener)
			{
				if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
					listener->OnEvent(this, EVENT_MOUSE_LEFTCLICK_DOWN);
				if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
					listener->OnEvent(this, EVENT_MOUSE_LEFTCLICK_UP);
			}
		}
	
	return true;
}

void GuiElement::AddChild(GuiElement* child)
{
	childs.push_back(child);
}

void GuiElement::RemoveChild(GuiElement* child)
{
	childs.remove(child);
	if (child->parent == this)
		child->parent = NULL;
}

void GuiElement::Activate()
{
	active = true;
	for (list<GuiElement*>::iterator item = childs.begin(); item != childs.end(); item++)
	{
		item._Ptr->_Myval->Activate();
	}
}

void GuiElement::ActivateChilds()
{
	if (active){
	for (list<GuiElement*>::iterator item = childs.begin(); item != childs.end(); item++)
	{
		item._Ptr->_Myval->active = true;
	}
	}
}
void GuiElement::DesactivateChilds()
{
	for (list<GuiElement*>::iterator item = childs.begin(); item != childs.end(); item++)
	{
		item._Ptr->_Myval->active = false;
	}
}



void GuiElement::Desactivate()
{
	active = false;
	for (list<GuiElement*>::iterator item = childs.begin(); item != childs.end(); item++)
	{
		item._Ptr->_Myval->Desactivate();
	}
}

void GuiElement::DrawDebug()
{
	SDL_Rect rect = GetScreenRect();
	rect.x -= App->render->camera.x;
	rect.y -= App->render->camera.y;

	App->render->DrawQuad(rect, 255, 0, 0, 1000, false);
}


GuiSlider::GuiSlider(iPoint p, SDL_Rect tex_1, SDL_Rect tex_2, int w, int thumb_h, iPoint offset, float value, GuiElement* par, j1Module* list)
: GuiElement(p, GUI_SLIDER, par, list), image({ offset.x, offset.y }, tex_1, this, NULL), thumb({ p.x + offset.x, thumb_h }, tex_2, this, NULL), width(w), thumb_pos(0), max_value(value)
{
	SetLocalRect({ p.x, p.y, width, tex_1.h });
	value = 0;
}

void GuiSlider::Draw()
{
	image.Draw();
	thumb.Draw();
}

void GuiSlider::Update(GuiElement* hover, GuiElement* focus)
{
	bool focused = (focus == this);
	
	int last_thumb = thumb_pos;
	

	if (thumb.CheckCollision(App->input->GetMousePosition()) && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
			iPoint m = App->input->GetMouseMotion();
			thumb_pos += m.x;
	}

	if (focused)
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			thumb_pos--;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			thumb_pos++;
	}

	
	if (clicking)
	{
		if (thumb.CheckCollision(App->input->GetMousePosition()) == false)
		{
			if (App->input->GetMousePosition().x > thumb.GetScreenPosition().x)
				thumb_pos++;
			else
				thumb_pos--;
		}
	}

	if (last_thumb != thumb_pos)
	{
		if (thumb_pos < 0 || thumb_pos > width)
		{
			if (thumb_pos < 0)
				thumb_pos = 0;
			else
				thumb_pos = width;
		}
		thumb.SetLocalPosition({ thumb_pos + image.GetLocalPosition().x, thumb.GetLocalPosition().y });

		listener->OnEvent(this, EVENT_SLIDER_CHANGE);
	}
}


float GuiSlider::GetValue()const
{
	float dvalue = max_value / width;
	return thumb_pos*dvalue;
}