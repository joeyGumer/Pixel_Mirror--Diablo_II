#include "EntItem.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"

EntItem::EntItem(const iPoint &p, uint ID) : EntStatic(p, ID)
{
	type = ITEM;
}

void EntItem::SetSprite(SDL_Rect r)
{
	tex = App->gui->GetAtlas();

	collider_rect.w = sprite_rect.w = sprite_dim.x = r.w;
	collider_rect.h = sprite_rect.h = sprite_dim.y = r.h;

	sprite_pivot = pivot = { sprite_rect.w, sprite_rect.h };

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	sprite = new Sprite(tex, pos, sprite_pivot, r);
	App->render->AddSpriteToList(sprite);
}
