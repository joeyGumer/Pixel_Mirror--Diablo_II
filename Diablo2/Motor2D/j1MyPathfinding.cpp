#include "j1App.h"
#include "j1MyPathfinding.h"
#include "j1Map.h"
#include "j1Render.h"
#include "p2Defs.h"
#include "p2Log.h"
#include <math.h>


j1MyPathfinding::j1MyPathfinding() : j1Module()
{
	name.create("pathfinding");
}

// Destructor
j1MyPathfinding::~j1MyPathfinding()
{}


bool j1MyPathfinding::SetLayer()
{
	p2List_item<MapLayer*>* layer = App->map->data.layers.start;
	while (layer)
	{
		if (layer->data->properties.Get("Navigation") == 1)
		{
			navigation_layer = layer->data;
			break;
		}
		layer = layer->next;
	}
	return true;
}

bool j1MyPathfinding::CleanUp()
{
	return true;
}


bool j1MyPathfinding::Astar(iPoint& start, iPoint& goal)
{
	ClearLists();
	SetLayer();

	bool found = false;
	
	if (!IsWalkable(start) || !IsWalkable(goal))
	{
		LOG("Goal Position is not walkable");
		return found;
	}

	if (start == goal)
	{
		LOG("Start is the goal");
		return found;
	}

	PathNode* first;
	first = new PathNode(start, NULL);

	first->g = 0;
	first->h = abs(goal.x - first->pos.x) + abs(goal.y - first->pos.y);
	first->f = first->h;

	open_nodes.add(first);

	while (open_nodes.start && found == false)
	{
		PathNode* q = FindNext();
		close_nodes.add(q);
		found = CreateChilds(q, goal);
	}

	if (found)
	{
		PathNode* way = close_nodes.end->data;

		while (way)
		{
			path.add(way);
			way = way->parent;
		}
	}
	return found;
}

PathNode* j1MyPathfinding::FindNext()
{
	p2List_item<PathNode*>* item = open_nodes.start;
	p2List_item<PathNode*>* node = open_nodes.start;

	while (item)
	{
		if (item->data->f < node->data->f)
			node = item;

		item = item->next;
	}

	PathNode* q = node->data;
	open_nodes.del(node);
	
	return q;
}

bool j1MyPathfinding::CreateChilds(PathNode* q, iPoint& goal)
{
	bool ret = false;

	for (int i = 0; i < 4; i++)
	{
		PathNode* child;
		child = new PathNode(q->pos, q);

		switch (i)
		{
		case 0:
			child->pos.x++;
			break;
		case 1:
			child->pos.y++;
			break;
		case 2:
			child->pos.x--;
			break;
		case 3:
			child->pos.y--;
			break;
		}

		if (child->pos == goal)
		{
			ret = true;
			close_nodes.add(child);
			break;
		}

		child->g = q->g + 1;
		child->h = abs(goal.x - child->pos.x) + abs(goal.y - child->pos.y);
		child->f = child->g + child->h;

		p2List_item<PathNode*>* item = open_nodes.start;

		while (item)
		{
			if (item->data->pos == child->pos && item->data->f <= child->f)
			{
				RELEASE(child);
				child = NULL;
				break;
			}
			item = item->next;
		}

		item = close_nodes.start;

		while (item && child)
		{
			if (item->data->pos == child->pos && item->data->f <= child->f)
			{
				RELEASE(child);
				child = NULL;
				break;
			}
			item = item->next;
		}

		if (child)
		{
			bool walkable = IsWalkable(child->pos);
			if (!walkable)
			{
				RELEASE(child);
				child = NULL;
			}
		}

		if (child)
			open_nodes.add(child);
	}

	return ret;
}

void j1MyPathfinding::ClearLists()
{
	p2List_item<PathNode*>* item = open_nodes.start;

	while (item)
	{
		if (item->data)
			RELEASE(item->data);
		item = item->next;
	}
	open_nodes.clear();

	item = close_nodes.start;

	while (item)
	{
		RELEASE(item->data);
		item = item->next;
	}
	close_nodes.clear();
	path.clear();
}

bool j1MyPathfinding::IsWalkable(iPoint& pos)
{
	if (pos.x >= App->map->data.width || pos.x < 0 ||
		pos.y >= App->map->data.height || pos.y <0)
		return false;

	
	if (navigation_layer->Get(pos.x, pos.y) == 0)
		return true;
	else
		return false;
}