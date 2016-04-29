#ifndef __ENT_PORTAL_H__
#define __ENT_PORTAL_H__

#include "EntStatic.h"

class j1Scene;

class EntPortal : public EntStatic
{
public:
	EntPortal(const iPoint &p, uint ID);
	~EntPortal();
	void SetAnimation();

	void Draw();
	void DrawDebug();

	void Teleport();
	void SetDestiny(j1Scene* dest);
public:
	j1Scene* destiny;
};

#endif