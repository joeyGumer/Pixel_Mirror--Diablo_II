#ifndef __j1PATHFINDING_H__
#define __j1PATHFINDING_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include <list>
#include <vector>

using namespace std;

#define DEFAULT_PATH_LENGTH 50
#define INVALID_WALK_CODE 255
#define NODE_CAPACITY 200

// --------------------------------------------------
// Recommended reading:
// Intro: http://www.raywenderlich.com/4946/introduction-to-a-pathfinding
// Details: http://theory.stanford.edu/~amitp/GameProgramming/
// --------------------------------------------------

struct PathNode;
// ---------------------------------------------------------------------
// Helper struct to include a list of path nodes
// ---------------------------------------------------------------------
struct PathList
{
	// Looks for a node in this list and returns it's list node or NULL
	list<PathNode*>::iterator Find(const iPoint& point);

	// Returns the Pathnode with lowest score in this list or NULL if empty
	list<PathNode*>::iterator GetNodeLowestScore();

	void Clear();
	// -----------
	list<PathNode*> nlist;
};

class j1PathFinding : public j1Module
{
public:

	j1PathFinding();

	// Destructor
	~j1PathFinding();

	// Called before quitting
	bool CleanUp();

	// Sets up the walkability map
	void SetMap(uint width, uint height, uchar* data);

	// Main function to request a path from A to B
	int CreatePath(const iPoint& origin, const iPoint& destination);

	// To request all tiles involved in the last generated path
	const vector<iPoint>* GetLastPath() const;

	// Utility: return true if pos is inside the map boundaries
	bool CheckBoundaries(const iPoint& pos) const;

	// Utility: returns true is the tile is walkable
	bool IsWalkable(const iPoint& pos) const;

	// Utility: return the walkability value of a tile
	uchar GetTileAt(const iPoint& pos) const;
	
	int GetNewPath(iPoint start, iPoint goal, vector<iPoint>& path);



private:

	// size of the map
	uint width;
	uint height;
	// all map walkability values [0..255]
	uchar* map;
	// we store the created path here
	vector<iPoint> last_path;
};

// ---------------------------------------------------------------------
// Pathnode: Helper struct to represent a node in the path creation
// ---------------------------------------------------------------------
struct PathNode
{
	// Convenient constructors
	PathNode();
	PathNode(float g, float h, const iPoint& pos, PathNode* parent);
	PathNode(PathNode& node);

	// Fills a list (PathList) of all valid adjacent pathnodes
	uint FindWalkableAdjacents(PathList& list_to_fill);
	// Calculates this tile score
	float Score() const;
	// Calculate the F for a specific destination tile
	float CalculateF(const iPoint& destination);

	// -----------
	float g;
	float h;
	iPoint pos;
	PathNode* parent;
};





#endif // __j1PATHFINDING_H__