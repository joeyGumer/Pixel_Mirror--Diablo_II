#ifndef __ENTITIES_H__
#define __ENTITIES_H__

#include "SDL\include\SDL.h"
#include "p2Point.h"
#include "Animation.h"

//NOTE: the copy paste is strong in this one,
//at least adapt it at the same style as our code :3
//and make a .h for declaration and a .cpp for definition (Carlos does it this way because he doesn't want to go from .h to .cpp)
//like this is just a mess
//and of course, becouse of the includes up there

//NOTE: got AIDS with this, at least the animation sprite_sheet is ready at the data.zip
enum ENTITY_TYPE
{
	ENEMY_DEBUG,
};

enum ENTITY_EVENT
{
	ENTITY_STATE_CHANGE,
};

enum ENTITY_STATE
{
	ENTITY_IDLE,
	ENTITY_WALKING,
	ENTITY_ATTACKING
};

enum ENTITY_INPUT
{
	ENTITY_INPUT_MOVE,
	ENTITY_INPUT_STOP_MOVE,
	ENTITY_INPUT_ATTACK,
	ENTITY_INPUT_NULL,
};

class Entity
{

public:

	//Constructors
	Entity(const iPoint &p, uint ID);

	//Destructor
	~Entity();

	//Update
	virtual bool Update(float dt) { return true;  }

	//Draw
	void Draw();

	//Debug Draw
	void DrawDebug();

	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	iPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;

	//Setters
	virtual void SetAnimations() {}

	//Events and states
	virtual void EntityEvent(ENTITY_EVENT even) {}
	virtual void StateMachine() {}

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

//Attributes
public:
	SDL_Rect		rect;
	ENTITY_TYPE		type;
	iPoint			pivot;
	iPoint			tile_pos;
	uint			id;

	Animation		current_animation;
	SDL_Texture*	sprite;
	SDL_Texture*    idle;
	Animation		idle_front;

	vector<iPoint>	path;
	iPoint			target;
	int				current_node;
	//NOTE: Declaration must be somewhere else
	float			target_radius = 70.5f;
	fPoint			velocity;
	bool			movement;
	bool			target_reached;
	bool			path_on = true;

	ENTITY_STATE		current_action;
	vector<Animation>	current_animation_set;
	ENTITY_INPUT		current_input;
	ENTITY_INPUT		previous_input = ENTITY_INPUT_NULL;


	

};

class entEnemyDebug : public Entity
{
public:

	entEnemyDebug(iPoint &position, uint id);

	bool Update(float dt);

	void SetAnimations();
	ENTITY_STATE UpdateAction();
	void EntityEvent(ENTITY_EVENT even);
	void StateMachine();

private:

};

#endif