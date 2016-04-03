#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#include <map>
#include <vector>

enum ENEMY_TYPE;
class j1Enemy;
using namespace std;

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

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	j1Enemy* Add(iPoint &pos, ENEMY_TYPE type);
	bool Remove(uint id);
	j1Enemy* GetEntity(uint id);

	j1Enemy* EntityOnMouse();

private:
	map<uint, j1Enemy*> active_entities;
	map<uint, j1Enemy*> inactive_entities;
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
};

#endif // __EntityManager_H__
