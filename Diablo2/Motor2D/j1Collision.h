#ifndef __J1Collision_H__
#define __J1Collision_H__

#include "j1Module.h"
#include <list>
#include "SDL\include\SDL.h"

using namespace std;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,

	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PARTICLE,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	j1Module* callback;

	Collider(SDL_Rect SDL_Rect, COLLIDER_TYPE type, j1Module* callback = NULL) : rect(SDL_Rect), type(type), callback(callback), to_delete(false)
	{ }

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(SDL_Rect &r) const;
};

class j1Collision : public j1Module
{

private:

	list<Collider*> colliders;

	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;

public:

	j1Collision();

	//Destructor
	~j1Collision();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = NULL);
	void DrawDebug(Collider* col);
};

#endif  __J1Collision_H__