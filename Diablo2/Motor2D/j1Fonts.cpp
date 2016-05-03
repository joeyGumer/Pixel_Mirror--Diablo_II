#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1FileSystem.h"
#include "j1Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

j1Fonts::j1Fonts() : j1Module()
{
	name.create("fonts");
}

// Destructor
j1Fonts::~j1Fonts()
{}

// Called before render is available
bool j1Fonts::Awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");
	bool ret = true;

	if(TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	else
	{
		const char* path = conf.child("default_font").attribute("file").as_string(DEFAULT_FONT);
		int size = conf.child("default_font").attribute("size").as_int(DEFAULT_FONT_SIZE);
		default = Load(path, size);
		path = conf.child("description_font").attribute("file").as_string();
		size = conf.child("description_font").attribute("size").as_int();
		description = Load(path, size);
	}

	return ret;
}

// Called before quitting
bool j1Fonts::CleanUp()
{
	LOG("Freeing True Type fonts and library");
	list<TTF_Font*>::iterator item;

	for(item = fonts.begin(); item != fonts.end(); item++)
	{
		TTF_CloseFont(*item);
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
TTF_Font* const j1Fonts::Load(const char* path, int size)
{
	TTF_Font* font = TTF_OpenFontRW(App->fs->Load(path), 1, size);
	
	if(font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
	}
	else
	{
		LOG("Successfully loaded font %s size %d", path, size);
		fonts.push_back(font);
	}

	return font;
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, SDL_Color color, TTF_Font* font)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface = TTF_RenderText_Blended((font) ? font : default, text, color);

	if(surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = App->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

SDL_Texture* j1Fonts::Print(const char* text, TextColor color, TTF_Font* font)
{
	switch (color)
	{
	case FONT_BLACK: return Print(text, { 0, 0, 0 }, font); break;
	case FONT_RED: return Print(text, { 255, 0, 0 },font); break;
	case FONT_GREEN: return Print(text, { 0, 255, 0 }, font); break;
	case FONT_BLUE:return  Print(text, { 0, 0, 255 }, font); break;
	case FONT_YELLOW: return Print(text, { 255, 255, 0 }, font); break;
	case FONT_WHITE: return Print(text, { 255, 255, 255 }, font); break;
	
	}
}

// calculate size of a text
bool j1Fonts::CalcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	bool ret = false;

	if(TTF_SizeText((font) ? font : default, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}