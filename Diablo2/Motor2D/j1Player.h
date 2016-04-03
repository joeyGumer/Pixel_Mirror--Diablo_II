#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//WARNING provisional sdl including
#include "SDL/include/SDL.h"
//NOTE: player speed, put it at the config file
#define PLAYER_SPEED 150.0f
#define DIRECTIONS 8
#define PLAYER_SPRITE_W int (96)
#define PLAYER_SPRITE_H int (92)
#define SPRITE_MARGIN int(1)
#define PLAYER_PIVOT_OFFSET int(10)

//NOTE: provisional, this will go somewhere alse to apply to all entities, or maybe deleted because the state machine
enum DIRECTION
{
	D_FRONT,
	D_FRONT_LEFT,
	D_LEFT,
	D_BACK_LEFT,
	D_BACK,
	D_BACK_RIGHT,
	D_RIGHT,
	D_FRONT_RIGHT,
};

enum PLAYER_EVENT
{
	HP_DOWN,
	HP_UP,
	MP_DOWN,
	MP_UP,
	STATE_CHANGE,
};

enum ACTION_STATE
{
	IDLE,
	WALKING,
	RUNNING,
	ATTACKING,
};

enum INPUT_STATE
{
	INPUT_MOVE,
	INPUT_STOP_MOVE,
	INPUT_ATTACK,
	INPUT_NULL,
};

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

	//Draws the player each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	//Debug mode
	void DrawDebug() const ;

	//Linear Movement
	//NOTE: this is just for the player, so, at the end, i don't see the need to do another module o r put it anywhere else
	void Move(float dt);
	void SetInitVelocity();
	void UpdateVelocity(float dt);
	bool IsTargetReached();

	//NOTE: some of these may go to the entities
	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	iPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;

	//Estructuralfunctions
	void SetAnimations();
	void SetDirection();

	//StateMachine functions
	ACTION_STATE UpdateAction();
	void StateMachine();

	//Utils
	void PlayerEvent(PLAYER_EVENT even);

	//Input
	void HandleInput();



//Attributes

public:

	
private:

	//Position
	iPoint p_position;
	iPoint p_pivot;
	
	//Linear movement
	//NOTE:
	iPoint		p_target;
	//NOTE: the declaration will go somewhere else
	float		target_radius = 2.5f;
	fPoint		p_velocity;
	bool		movement;

	//Textures
	SDL_Texture* p_debug = NULL;
	SDL_Texture* p_sprite = NULL;
	SDL_Texture* p_idle = NULL;
	SDL_Texture* p_walk = NULL;

	//Rects for each state and direction
	//--------------------
	Animation current_animation;
	//Idle
	//NOTE : Can i make this more elegant (maybe with a list)
	Animation idle_front;
	Animation idle_left_front;
	Animation idle_left;
	Animation idle_left_back;
	Animation idle_back;
	Animation idle_right_back;
	Animation idle_right;
	Animation idle_right_front;

	Animation walk_front;
	Animation walk_left_front;
	Animation walk_left;
	Animation walk_left_back;
	Animation walk_back;
	Animation walk_right_back;
	Animation walk_right;
	Animation walk_right_front;
	//--------------------

	//Attributes
	int HP_max;
	int HP_current;

	int MP_max;
	int MP_current;

	//StateMachine Attributes
	ACTION_STATE	current_action;
	DIRECTION		current_direction;
	INPUT_STATE		current_input;

};

#endif // __j1PLAYER_H__

