#include "EntItem.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"
#include "j1SceneManager.h"
#include "j1Scene.h"

EntItem::EntItem(const iPoint &p, uint ID) : EntStatic(p, ID)
{
	type = ITEM;
}

EntItem::~EntItem()
{
	App->sm->current_scene->entity_list.remove(this);

	if (!convert)
		RELEASE(nexus);
}

void EntItem::SetSprite(SDL_Rect r)
{
	tex = App->gui->GetAtlas();

	collider_rect.w = sprite_rect.w = sprite_dim.x = r.w;
	collider_rect.h = sprite_rect.h = sprite_dim.y = r.h;

	sprite_pivot = pivot = { sprite_rect.w, sprite_rect.h};

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	sprite = new Sprite(tex, pos, sprite_pivot, r);
	App->render->AddSpriteToList(sprite);
}

void EntItem::DrawDebug()
{
	App->render->DrawQuad(GetPlayerRect(), 255, 0, 0, 255, false);

	App->render->DrawCircle(position.x, position.y, 2, 255, 0, 0);
}