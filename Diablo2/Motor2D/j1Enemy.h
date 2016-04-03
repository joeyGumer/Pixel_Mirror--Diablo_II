#include "SDL\include\SDL.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1App.h"

enum ENEMY_TYPE
{
	ENEMY_DEBUG,
};

class j1Enemy
{

public:

	SDL_Rect		dim;
	ENEMY_TYPE		type;
	SDL_Texture*	tex;
	uint			id;
	iPoint			tile_pos;

	//Constructors
	j1Enemy(const iPoint &p, uint ID)
	{
		iPoint tmp = App->map->WorldToMap(p.x, p.y);
		tile_pos = tmp;
		tmp = App->map->MapToWorld(tmp.x, tmp.y);
		dim.x = tmp.x;
		dim.y = tmp.y;
		id = ID;
	};

	//Destructor
	~j1Enemy()
	{
		SDL_DestroyTexture(tex);
	}

	void Draw()
	{
		App->render->Blit(tex, dim.x, dim.y);
	}

};

class EnemyDebug : public j1Enemy
{
public:

	EnemyDebug(iPoint &p, uint id) : j1Enemy(p, id)
	{
		tex = App->tex->Load("textures/enemy1.png");
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);

		type = ENEMY_DEBUG;
	}
};