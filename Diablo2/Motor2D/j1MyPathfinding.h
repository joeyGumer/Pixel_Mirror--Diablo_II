#ifndef _J1MYPATHFINDING_H_
#define _J1MYPATHFINDING_H_

#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"

struct MapLayer;

struct PathNode
{
	PathNode(iPoint& p, PathNode* node)
	{
		pos = p;
		parent = node;
	}
	//parent node
	PathNode*	parent;
	//position coordinates
	iPoint pos;
	
	//important data of the node:
	//g: cost to arrive to this node (distance run form init)
	//h: cost to arrive to the goal
	//f: g + h, so, the number of steps to do if going trough this node
	float		g;
	float		h;
	float		f;
};


class j1MyPathfinding : public j1Module
{
public:
	// Constructor
	j1MyPathfinding();

	// Destructor
	virtual ~j1MyPathfinding();

	// Called before render is available
	bool SetLayer();
	//Have to think how to do it with the update functions
	// Called before all Updates
	/*bool PreUpdate();*/
	// Called before quitting
	bool CleanUp();

	// A* pathfinding algorithm
	bool Astar(iPoint& start, iPoint& goal);
	PathNode* FindNext();
	bool CreateChilds(PathNode* q, iPoint& goal);
	bool IsWalkable(iPoint& pos);
	void ClearLists();
	

public:
	p2List<PathNode*> open_nodes;
	p2List<PathNode*> close_nodes;
	p2List<PathNode*> path;

	MapLayer* navigation_layer;
};

#endif _J1MYPATHFINDING_H_