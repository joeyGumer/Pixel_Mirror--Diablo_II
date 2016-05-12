#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#include <map>
#include <vector>

enum ENTITY_TYPE;
enum ENEMY_TYPE;
class Entity;
class GuiLabel;
using namespace std;

#define UPDATE_MARGIN 75

class j1EntityManager : public j1Module
{

public:

	j1EntityManager();

	// Destructor
	virtual ~j1EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Update
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//Collision
	void OnCollision(Collider* c1, Collider* c2);

	Entity* Add(iPoint &pos, ENTITY_TYPE type);
	Entity* AddEnemy(iPoint &pos, ENEMY_TYPE type);
	Entity* AddEnemyMap(iPoint &pos, ENEMY_TYPE type);
	bool Remove(uint id);
	Entity* GetEntity(uint id);

	Entity* EntityOnMouse();
	Entity* EntityOnCoords(iPoint &pos);

private:
	map<uint, Entity*> active_entities;
	map<uint, Entity*> inactive_entities;
	//selection
	//selection_ordered
	uint next_ID;
	//uchar filter;

	//SDL_Rect selector;

	void DrawAll();
	//void SelectAll(uchar filter);
	//SelectAvailable
	//void calculateSelector
	//void sortEntities

public:
	//Wolf textures
	SDL_Texture* wolf_idle;
	SDL_Texture* wolf_walk;
	SDL_Texture* wolf_attack;
	SDL_Texture* wolf_death;

	//Crawler textures
	SDL_Texture* crawler_idle;
	SDL_Texture* crawler_walk;
	SDL_Texture* crawler_attack;
	SDL_Texture* crawler_death;

	//Boss textures
	SDL_Texture* boss_idle;
	SDL_Texture* boss_walk;
	SDL_Texture* boss_attack;
	SDL_Texture* boss_cast;
	SDL_Texture* boss_death;

	//Shaman textures
	SDL_Texture* shaman_idle;
	SDL_Texture* shaman_walk;
	SDL_Texture* shaman_attack;
	SDL_Texture* shaman_death;

	//Shaman particles
	SDL_Texture* shaman_particle;

	//Summoner textures
	SDL_Texture* summoner_idle;
	SDL_Texture* summoner_walk;
	SDL_Texture* summoner_attack;
	SDL_Texture* summoner_death;

	//Summoner particles
	SDL_Texture* summoner_particle;

	//Izual textures
	SDL_Texture* izual_idle;
	SDL_Texture* izual_walk;
	SDL_Texture* izual_attack;
	SDL_Texture* izual_cast;
	SDL_Texture* izual_death;

	//Izual particles
	SDL_Texture* izual_particle;

	//Portal texture
	SDL_Texture* portal_tex;

	//Texture list
	list<SDL_Texture*> texture_list;

	//Sounds
	int crawler_attackfx;
	int crawler_gethitfx;
	int crawler_deathfx;

	int wolf_attackfx;
	int wolf_gethitfx;
	int wolf_deathfx;

	GuiLabel* enemy_name = NULL;
};

#endif // __EntityManager_H__
