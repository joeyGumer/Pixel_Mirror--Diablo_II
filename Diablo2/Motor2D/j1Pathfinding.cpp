#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "ExtraSTL.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH),width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");
	last_path.clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
			pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if(CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const vector<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
list<PathNode*>::iterator PathList::Find(const iPoint& point) 
{
	list<PathNode*>::iterator item = nlist.begin();
	while(item != nlist.end())
	{
		if((*item)->pos == point)
			return item;
		item++;
	}
	return nlist.end();
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
list<PathNode*>::iterator PathList::GetNodeLowestScore() 
{
	list<PathNode*>::reverse_iterator tmp = nlist.rend();
	int min = 65535;

	list<PathNode*>::reverse_iterator item = nlist.rbegin();
	while(item != nlist.rend())
	{
		if((*item)->Score() < min)
		{
			min = (*item)->Score();
			tmp = item;
		}
		item++;
	}

	if (tmp != nlist.rend())
		for (list<PathNode*>::iterator ret = nlist.begin(); ret != nlist.end(); ret++)
		{
			if (*ret == *tmp)
				return ret;
		}
	
	return nlist.end();
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, PathNode* p) : g(g), h(h), pos(pos), parent(p)
{}

PathNode::PathNode(PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill) 
{
	iPoint cell;
	uint before = list_to_fill.nlist.size();

	// north
	cell.create(pos.x, pos.y + 1);
	if (App->pathfinding->IsWalkable(cell))
	{
		PathNode* child;
		child = new PathNode(-1, -1, cell, this);
		list_to_fill.nlist.push_back(child);
	}

	// south
	cell.create(pos.x, pos.y - 1);
	if(App->pathfinding->IsWalkable(cell))
	{
		PathNode* child;
		child = new PathNode(-1, -1, cell, this);
		list_to_fill.nlist.push_back(child);
	}

	// east
	cell.create(pos.x + 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
	{
		PathNode* child;
		child = new PathNode(-1, -1, cell, this);
		list_to_fill.nlist.push_back(child);
	}

	// west
	cell.create(pos.x - 1, pos.y);
	if(App->pathfinding->IsWalkable(cell))
	{
		PathNode* child;
		child = new PathNode(-1, -1, cell, this);
		list_to_fill.nlist.push_back(child);
	}

	return list_to_fill.nlist.size();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int j1PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	last_path.clear();

	int steps = 0;
	if (!IsWalkable(origin) || !IsWalkable(destination))
		return -1;

	PathList open_nodes;
	PathList close_nodes;
	PathNode* start;
	start = new PathNode(0, abs(destination.x - origin.x) + abs(destination.y - origin.y), origin, NULL);

	open_nodes.nlist.push_back(start);

	while (open_nodes.nlist.begin() != open_nodes.nlist.end())
	{ 
		list<PathNode*>::iterator tmp = open_nodes.GetNodeLowestScore();
		PathNode* q = (*tmp);
	
		close_nodes.nlist.push_back(q);
		open_nodes.nlist.erase(tmp);

		//Capped pathfinding so it does not search for ridiculous distances
		if (close_nodes.nlist.size() >= NODE_CAPACITY)
		{
			close_nodes.Clear();
			open_nodes.Clear();
			return -1;
		}

		if (q->pos == destination)
		{
			PathNode* track = q;
			while (track->pos != origin)
			{
				last_path.push_back(track->pos);
				steps++;
				track = track->parent;
			}
			

			//Swap for vector
			for (int start = 0, end = last_path.size() - 1; start < end; start++, end--)
				SWAP(last_path[start], last_path[end]);
			//

			close_nodes.Clear();
			open_nodes.Clear();
			return steps;
		}

		PathList adjacent_nodes;
		q->FindWalkableAdjacents(adjacent_nodes);

		list<PathNode*>::iterator child = adjacent_nodes.nlist.begin();
		for (; child != adjacent_nodes.nlist.end(); child++)
		{
			if (close_nodes.Find((*child)->pos) != close_nodes.nlist.end())
				continue;
			
			(*child)->CalculateF(destination);
			list<PathNode*>::iterator check = open_nodes.Find((*child)->pos);
			if (check != open_nodes.nlist.end())
			{
				if ((*child)->g < (*check)->g)
				{
					(*check)->parent = (*child)->parent;
					(*check)->g = (*child)->g;
					RELEASE(*child);
					continue;
				}
			}
			else
				open_nodes.nlist.push_back(*child);
		}

		adjacent_nodes.nlist.clear();
	}

	return -1;
}


void PathList::Clear()
{
	list<PathNode*>::iterator item = nlist.begin();

	for (; item != nlist.end(); item++)
	{
		RELEASE(*item);
	}

	nlist.clear();
}

int j1PathFinding::GetNewPath(iPoint start, iPoint goal, vector<iPoint>& path)
{
	if (start == goal)
		return -1;

	int steps = CreatePath(start, goal);
	path.clear();
	path = last_path;

	return steps;
}