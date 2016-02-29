#include "GuiElements.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Textures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )



//Constructors 
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

GuiLabel::GuiLabel(p2SString t, _TTF_Font* f, iPoint p, GuiElement* par, j1Module* list = NULL) 
	: GuiElement(p, GUI_LABEL, par, list), text(t), font(f)
{
	//Have to polish the texture sistem in the label
	tex = App->font->Print(text.GetString());
	tex_rect = { 0, 0, 0, 0 };
	App->font->CalcSize(text.GetString(), tex_rect.w, tex_rect.h);
	SetLocalRect({ p.x, p.y, tex_rect.w, tex_rect.h });
}

GuiImage::GuiImage(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list = NULL) 
	: GuiElement(p, r, GUI_IMAGE, par, list)
{}

//I'm doing and especific constructor, have to change this
GuiInputBox::GuiInputBox(p2SString t, _TTF_Font* f, iPoint p, int width, SDL_Rect r, iPoint offset, GuiElement* par, j1Module* list)
	: GuiElement(p, r, GUI_INPUTBOX, par, list), text(t, f, { 0, 0 }, this), image({ offset.x, offset.y }, r, this)
{
	SetLocalRect({ p.x, p.y, width, text.GetLocalRect().h});
	//like this, we move the image
	image.Center(true, true);
	inputOn = false;
	init = false;
	password = false;
	cursor_pos = 0;

	App->font->CalcSize("A", cursor.x, cursor.y);
	cursor.x = 0;
}
//-----

//Draw functions
void GuiImage::Draw()
{
	iPoint p = GetScreenPosition();
	//For now without mask, it gives some problems
	/*if (parent && parent->mask)
	{
		SDL_Rect r = parent->GetScreenRect();

		App->render->SetViewPort({ r.x , r.y , r.w, r.h });
		p = GetLocalPosition();
	}*/

	//Change the camera application to the GetScreenPositionFunction
	App->render->Blit(App->gui->GetAtlas(),
		p.x - App->render->camera.x,
		p.y - App->render->camera.y,
		&tex_rect);

	/*if (parent && parent->mask)
		App->render->ResetViewPort();*/
}

void GuiLabel::Draw()
{
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
//

//Update functions
void GuiImage::Update(GuiElement* hover, GuiElement* focus)
{
	//Nothing
}

void GuiLabel::Update(GuiElement* hover, GuiElement* focus)
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

			//Password mode
			//It stills has problems
			/*if (password)
			{
				added_text.Fill('*');
				text.tex = App->font->Print(added_text.GetString());
			}*/

			cursor_pos = changed_cursor;
			if (cursor_pos > 0)
			{
				//Don't know why need to do this like this, ask ric
				p2SString selection(100);
				selection.Reserve(added_text.Length() * 2);
				//
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
//GuiLabel Functions
void GuiLabel::SetText(p2SString t)
{
	if (tex)
		SDL_DestroyTexture(tex);

	text = t.GetString();
	tex = App->font->Print(text.GetString());
	
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

bool GuiElement::CheckEvent(GuiElement* hover, GuiElement* focus)
{
	bool inside = (hover == this);
	bool focused = (focus == this);
	

		if (inside != mouseIn)
		{
			if (listener)
			{
				if (inside)
					listener->OnEvent(this, EVENT_MOUSE_ENTER);
				else
					listener->OnEvent(this, EVENT_MOUSE_EXIT);
			}
			mouseIn = inside;
		}
		
		if (inside)
		{
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

void GuiElement::DrawDebug()
{
	SDL_Rect rect = GetScreenRect();
	rect.x -= App->render->camera.x;
	rect.y -= App->render->camera.y;

	App->render->DrawLine(rect.x, rect.y, rect.x + rect.w, rect.y, 255, 0, 0);
	App->render->DrawLine(rect.x, rect.y, rect.x, rect.y + rect.h, 255, 0, 0);
	App->render->DrawLine(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, 255, 0, 0);
	App->render->DrawLine(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h, 255, 0, 0);

}

//EXERCISE 1
//EXERCISE 6 //The offsets are applied at the constructor
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
	
	//EXERCISE 2
	if (thumb.CheckCollision(App->input->GetMousePosition()) && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
			iPoint m = App->input->GetMouseMotion();
			thumb_pos += m.x;
	}
	//----------

	//EXERCISE 3
	if (focused)
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			thumb_pos--;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			thumb_pos++;
	}

	//EXERCISE 4
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

	//APPLIED AT EXERCISE 2 BUT FOR ALL OF THEM
	//activated only when the thumb position is changed so it has not to be used on every frame
	if (last_thumb != thumb_pos)
	{
		if (thumb_pos < 0 || thumb_pos > width)
		{
			if (thumb_pos < 0)
				thumb_pos = 0;
			else
				thumb_pos = width;
		}
		//I apply some offset
		thumb.SetLocalPosition({ thumb_pos + image.GetLocalPosition().x, thumb.GetLocalPosition().y });

		listener->OnEvent(this, EVENT_SLIDER_CHANGE);
	}
}

//EXERCISE 5
float GuiSlider::GetValue()const
{
	float dvalue = max_value / width;
	return thumb_pos*dvalue;
}