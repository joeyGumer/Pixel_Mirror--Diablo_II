#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
//WARNING provisional sdl including
#include "SDL/include/SDL.h"
//NOTE: player speed, put it at the config file
#define PLAYER_SPEED 200.0f
#define DIRECTIONS 8
#define PLAYER_W int (96)
#define PLAYER_H int (92)
#define PLAYER_PIVOT_OFFSET int(10)




class j1Player : public j1Module
{
//Methods

public:
	j1Player();

	//Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called the first frame
	bool Start();

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	// Called each loop iteration
	void Draw() const;

	// Called before quitting
	bool CleanUp();

	//NOTE: some of these may go to the entities
	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	iPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;



//Attributes

public:

	
private:

	//Position
	iPoint p_map_pos;
	iPoint p_pivot;

	//Textures
	SDL_Texture* p_debug = NULL;
	SDL_Texture* p_sprite = NULL;

	//
	//------Rects for each state and direction
	//
	SDL_Rect current_sprite;
	//Idle
	//NOTE : later this will be an animation
	SDL_Rect idle_front;
	SDL_Rect idle_left_front;
	SDL_Rect idle_left;
	SDL_Rect idle_left_back;
	SDL_Rect idle_back;
	SDL_Rect idle_right_back;
	SDL_Rect idle_right;
	SDL_Rect idle_right_front;

};

#endif // __j1PLAYER_H__

