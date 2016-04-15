#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include <list>

using namespace std;
//NOTE : put this to the config file
#define CAM_SPEED 200.0f
#define INIT_POS_X 280
#define INIT_POS_Y 0

struct Sprite
{
	Sprite();
	Sprite(SDL_Texture* texture, SDL_Rect* positionMap, SDL_Rect* sectionTexture);
	~Sprite();

	SDL_Texture*	texture;
	SDL_Rect		positionMap;
	SDL_Rect		sectionTexture;

	int				y;


};


class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;
	iPoint WorldToScreen(int x, int y) const;
	void CenterCamera(int x, int y);

	// Draw & Blit
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	
	//blit sprites
	//NOTE: With list
	bool AddSpriteToList(Sprite* sprite);
	bool DrawSprite(Sprite* sprite, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
	bool SortSprites();
	// Set background color
	void SetBackgroundColor(SDL_Color color);
	

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;

	//Note: sprites list & multimap
	list<Sprite*>	sprites;
	list<Sprite*>::iterator iterator;
	
	
};

#endif // __j1RENDER_H__