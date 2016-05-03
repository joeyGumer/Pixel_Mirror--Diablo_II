#include "j1App.h"
#include "j1Collision.h"
#include "j1Input.h"
#include "j1Render.h"
#include "p2Log.h"

j1Collision::j1Collision() : j1Module()
{
	name.create("collision");

	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PARTICLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PARTICLE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_PARTICLE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PARTICLE][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PARTICLE][COLLIDER_PARTICLE] = false;
}

j1Collision::~j1Collision()
{}

bool j1Collision::Awake(pugi::xml_node&)
{
	return true;
}

bool j1Collision::Start()
{
	return true;
}


bool j1Collision::PreUpdate()
{
	//Remove all colliders scheduled for deletion
	list<Collider*>::iterator tmp = colliders.begin();

	while (tmp != colliders.end())
	{
		if ((*tmp)->to_delete == true)
		{
			RELEASE(*tmp);
			tmp = colliders.erase(tmp);
		}
		else
			++tmp;
	}

	return true;
}

bool j1Collision::Update(float dt)
{
	// Debug ---
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	list<Collider*>::iterator it1 = colliders.begin();
	list<Collider*>::iterator it2;

	Collider *c1;
	Collider *c2;

	while (it1 != colliders.end())
	{
		c1 = (*it1);

		// Debug ---
		if (debug)
			DrawDebug(c1);

		it2 = next(it1);				 //avoid checking collisions already checked
		while (it2 != colliders.end())
		{
			c2 = (*it2);

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
			++it2;
		}
		++it1;
	}

	return true;
}

void j1Collision::DrawDebug(Collider *col)
{
	Uint8 alpha = 80;
	switch (col->type)
	{
	case COLLIDER_NONE:
		App->render->DrawQuad(col->rect, 255, 255, 255, alpha, false);
		break;
	case COLLIDER_PLAYER:
		App->render->DrawQuad(col->rect, 0, 255, 255, alpha, false);
		break;
	case COLLIDER_ENEMY:
		App->render->DrawQuad(col->rect, 255, 0, 255, alpha, false);
		break;
	case COLLIDER_PARTICLE:
		App->render->DrawQuad(col->rect, 0, 0, 255, alpha, false);
		break;
	}
}

bool j1Collision::CleanUp()
{
	LOG("Freeing all colliders");
	list<Collider*>::reverse_iterator item = colliders.rbegin();

	while (item != colliders.rend())
	{
		RELEASE(*item);
		++item;
	}

	colliders.clear();
	return true;
}

Collider* j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret); //put the collider at the end of the list
	return ret;
}

bool Collider::CheckCollision(SDL_Rect &r) const
{
	return (bool)SDL_HasIntersection(&rect, &r);
}