#include "EntItem.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"

EntItem::EntItem(const iPoint &p, uint ID, SDL_Rect r) : EntStatic(p, ID)
{
	type = ITEM;

	tex = App->gui->GetAtlas();
	sprite_rect = { 0, 0, r.w, r.h };
	sprite_pivot = pivot = { sprite_rect.w, sprite_rect.h };

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	sprite = new Sprite(tex, pos, sprite_pivot, r);
	App->render->AddSpriteToList(sprite);
}
