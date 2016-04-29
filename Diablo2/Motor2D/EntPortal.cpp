#include "EntPortal.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1EntityManager.h"
#include "j1SceneManager.h"

EntPortal::EntPortal(const iPoint &p, uint ID) : EntStatic(p, ID)
{
	type = PORTAL;
	tex = App->game->em->portal_tex;
	SetAnimation();

	//Sprite creation

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	SDL_Rect current_sprite = sprite_rect;
	sprite = new Sprite(tex, pos, sprite_pivot, current_sprite);
	App->render->AddSpriteToList(sprite);
}

EntPortal::~EntPortal()
{

}

void EntPortal::SetAnimation()
{
	sprite_rect = collider_rect = { 0, 0, 78, 130 };

	sprite_pivot = pivot = { collider_rect.w / 2, collider_rect.h - 20};

	//NOTE: Set Particle Animation Here

}

//Drawing methods
void EntPortal::Draw()
{
	//iPoint pos = GetBlitPosition();

	if (sprite)
	{
		fPoint p = GetPivotPosition();
		iPoint pos(p.x, p.y);
		sprite->UpdateSprite(tex, pos, sprite_pivot, sprite_rect);
	}

	//NOTE: Draw Particle Animation here

}

void EntPortal::DrawDebug()
{
	iPoint t_pos = GetTilePosition();
	fPoint p_pos = GetPivotPosition();
	SDL_Rect rect = GetPlayerRect();

	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0, 255, false);

	App->render->DrawQuad(rect, 255, 0, 0, 255, false);
}

void EntPortal::SetDestiny(j1Scene* dest)
{
	destiny = dest;
}