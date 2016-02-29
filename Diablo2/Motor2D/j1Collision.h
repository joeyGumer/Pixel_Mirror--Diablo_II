#ifndef __J1Collision_H__
#define __J1Collision_H__

/*
#include "j1Module.h"
#include "p2List.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	j1Module* callback;

	p2Point<int> posLevel;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)

	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	p2Point<int> GetPosLevel();

	bool CheckCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision(Application* app, bool start_enabled = true);
	~ModuleCollision();

	bool PreUpdate();
	bool Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void DrawDebug(Collider* col);

private:

	p2List<Collider*>	colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};
*/

#endif  __J1Collision_H__