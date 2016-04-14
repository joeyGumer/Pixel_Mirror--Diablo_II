
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"


#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name.create("renderer");
	background.r = 0;
	background.g = 0;
	background.b = 0;
	background.a = 0;
}

// Destructor
j1Render::~j1Render()
{}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");
	bool ret = true;
	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		camera.w = App->win->screen_surface->w;
		camera.h = App->win->screen_surface->h;
		camera.x = INIT_POS_X;
		camera.y = INIT_POS_Y;
	}

	return ret;
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);

	//NOTE: My camera cooling, very simple and works, buts ask ric about if this is cheating
	SetViewPort({ 0, 0 ,camera.w, camera.h });
	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool j1Render::PostUpdate()
{
	// NOTE:iterate list sprites call function sort and blit
	iterator = sprites.begin();
	for (iterator; iterator != sprites.end(); iterator++)
	{
		//insert sort function here
		DrawSprite(*iterator);
	}
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	// erase list Sprites
	list<Sprite*>::iterator i = sprites.begin();
	while (i != sprites.end())
	{
		++i;
	}
	sprites.clear();

	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Load Game State
bool j1Render::Load(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

iPoint j1Render::WorldToScreen(int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x + camera.x / scale);
	ret.y = (y - camera.x / scale);

	return ret;
}

void j1Render::CenterCamera(int x, int y)
{
	uint win_x;
	uint win_y;
	App->win->GetWindowSize(win_x, win_y);

	camera.x = (win_x / 2) - x;
	camera.y = (win_y / 2) - y;
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, float speed, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;

	//Camera culling
	if (section)
		if (!(x + section->w > -camera.x && x < -camera.x + camera.w &&
			y + section->h > -camera.y && y < -camera.y + camera.h))
			return false;
	//
		uint scale = App->win->GetScale();

		SDL_Rect rect;
		rect.x = (int)(camera.x * speed) + x * scale;
		rect.y = (int)(camera.y * speed) + y * scale;

		if (section != NULL)
		{
			rect.w = section->w;
			rect.h = section->h;
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		}

		rect.w *= scale;
		rect.h *= scale;

		SDL_Point* p = NULL;
		SDL_Point pivot;

		if (pivot_x != INT_MAX && pivot_y != INT_MAX)
		{
			pivot.x = pivot_x;
			pivot.y = pivot_y;
			p = &pivot;
		}

		if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	

	return ret;
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	int result = -1;

	if(use_camera)
		result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else
		result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool j1Render::DrawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera) const
{
	bool ret = true;
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	
	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	if (use_camera)
	{
		x *= scale;
		y *= scale;
		x += camera.x;
		y += camera.y;
	}

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor) * scale);
		points[i].y = (int)(y + radius * sin(i * factor) * scale);
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result != 0)
	{
		LOG("Cannot draw circle to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
//NOTE: Sprites functions

//NOTE: Add Sprite to the list of Sprites
bool j1Render::AddSpriteToList(Sprite* sprite)
{
	bool ret = true;
	if (sprite != NULL)
	{
		if (sprite->texture != NULL)
		{	
			sprites.push_back(sprite);
			LOG("Sprite put correct inside of list");
		}
		else
		{
			LOG("Error. No put list. Texture is empty");
		}
	}
	else
	{
		LOG("Error, this sprite is not correct.");
	}
	return ret;
}
//NOTE: Blit Sprite
bool j1Render::DrawSprite(Sprite* sprite, float speed, double angle, int pivot_x, int pivot_y)
{
	bool ret = true;

	uint scale = App->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x) + sprite->positionMap.x * scale;
	rect.y = (int)(camera.y) + sprite->positionMap.y * scale;


	SDL_QueryTexture(sprite->texture, NULL, NULL, &rect.w, &rect.h);


	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	pivot.x = pivot.y = INT_MAX;

	if (SDL_RenderCopyEx(renderer, sprite->texture, NULL, &rect, 0, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
	}
	
	return ret;

}
//NOTE: Constructors of struct Sprites
Sprite::Sprite()
{
	LOG("Constructor empty Sprite");
}

Sprite::Sprite(SDL_Texture* texture, SDL_Rect* positionMap, SDL_Rect* sectionTexture)
{
	texture = this->texture;
	positionMap = &this->positionMap;
	sectionTexture = &this->sectionTexture;
	

}
//NOTE: Destructor
Sprite::~Sprite()
{
	LOG("Destructor");
	SDL_DestroyTexture(texture);

}

