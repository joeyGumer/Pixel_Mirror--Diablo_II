#include "SDL\include\SDL.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1App.h"
#include "Animation.h"

//NOTE: the copy paste is strong in this one,
//at least adapt it at the same style as our code :3
//and make a .h for declaration and a .cpp for definition (Carlos does it this way because he doesn't want to go from .h to .cpp)
//like this is just a mess
//and of course, becouse of the includes up there

//NOTE: got AIDS with this, at least the animation sprite_sheet is ready at the data.zip
enum ENEMY_TYPE
{
	ENEMY_DEBUG,
};

class j1Enemy
{

public:

	SDL_Rect		dim;
	ENEMY_TYPE		type;
	uint			id;
	iPoint			tile_pos;
	
	//Animations
	SDL_Rect		current_sprite;
	SDL_Texture*    idle;
	Animation		idle_front;




	//Constructors
	j1Enemy(const iPoint &p, uint ID)
	{
		//NOTE: wow, this will need to be adapted well, look how it's done with the player (i refer to the map - world conversion, and positioning through a pivot)
		iPoint tmp = App->map->WorldToMap(p.x, p.y);
		tile_pos = tmp;
		tmp = App->map->MapToWorld(tmp.x, tmp.y);
		dim.x = tmp.x;
		dim.y = tmp.y;
		id = ID;
	};

	//DestructoR
	~j1Enemy()
	{
		SDL_DestroyTexture(idle);
	}

	void Draw()
	{
		App->render->Blit(idle, dim.x, dim.y);
	}
};

class EnemyDebug : public j1Enemy
{
public:

	EnemyDebug(iPoint &p, uint id) : j1Enemy(p, id)
	{
		idle = App->tex->Load("textures/enemy1.png");
		SDL_QueryTexture(idle, NULL, NULL, &dim.w, &dim.h);

		type = ENEMY_DEBUG;
	}
};