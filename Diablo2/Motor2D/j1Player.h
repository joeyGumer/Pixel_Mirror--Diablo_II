#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//WARNING provisional sdl including
#include "SDL/include/SDL.h"
#include <vector>

using namespace std;

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
	D_DEFAULT
};

enum PLAYER_EVENT
{
	HP_DOWN,
	HP_UP,
	MP_DOWN,
	MP_UP,
	ST_DOWN,
	ST_UP,
	STATE_CHANGE,
};

enum ACTION_STATE
{
	IDLE,
	WALKING,
	RUNNING,
	ATTACKING,
	DEFAULT,
};

enum INPUT_STATE
{
	INPUT_MOVE,
	INPUT_STOP_MOVE,
	INPUT_ATTACK,
	INPUT_NULL,
};

class Entity;

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

	//Movement
	void Move(float dt);
	void SetMovement(int x, int y);
	void SetInitVelocity();
	void SetTarget(iPoint target);
	void SetNewPath(int x, int y);
	void UpdateVelocity(float dt);
	void UpdateMovement(float dt);
	bool IsTargetReached();
	void GetNewTarget();
	
	//Attack
	bool IsInRange(Entity* enemy);
	void UpdateAttack();

	//NOTE: some of these may go to the entities
	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	fPoint		GetPivotPosition() const;
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
	fPoint p_position;
	iPoint p_pivot;
	
	//Movement
	//NOTE: All this will be used with the moving unities too
	vector<iPoint> path;
	iPoint		p_target;
	int			p_current_node;
	//NOTE: the declaration will go somewhere else
	float		target_radius = 2.5f;
	fPoint		p_velocity;
	bool		movement;
	bool		target_reached;
	bool		path_on = true;

	//Attack
	bool		attacking;

	//Textures
	SDL_Texture* p_debug = NULL;
	SDL_Texture* p_sprite = NULL;
	SDL_Texture* p_idle = NULL;
	SDL_Texture* p_walk = NULL;
	SDL_Texture* p_attack = NULL;

	//Rects for each state and direction
	//--------------------
	Animation* current_animation;
	//Idle
	//NOTE : Can i make this more elegant (maybe with a list)
	vector<Animation> idle;
	vector<Animation> walk;
	vector<Animation> attack;
	//--------------------

	//Attributes
	int HP_max;
	int HP_current;

	int MP_max;
	int MP_current;

	float ST_max;
	float ST_current;


	float attack_range = 65.0f;

	//StateMachine Attributes
	ACTION_STATE	current_action;
	vector<Animation> current_animation_set;
	DIRECTION		current_direction;
	INPUT_STATE		current_input;
	INPUT_STATE		previous_input = INPUT_NULL;

	//NOTE: will be cahnged to a enemy once entity manager structure is changed
	//Enemy target
	Entity* enemy;

};

#endif // __j1PLAYER_H__

