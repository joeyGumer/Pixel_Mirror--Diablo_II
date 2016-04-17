#include "EntItem.h"
#include "j1Player.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Gui.h"
#include "j1Render.h"

EntItem::EntItem(const iPoint &p, uint ID) : EntStatic(p, ID)
{

}

itmPotionHP::itmPotionHP(const iPoint &p, uint ID) : EntItem(p, ID)
{
	type = ITEM_HEALTH;
	//NOTE:
	tex = App->gui->GetAtlas();
	sprite_rect = collider_rect = { 0, 0, 29, 29 };
	sprite_pivot = pivot = { sprite_rect.w, sprite_rect.h };

	fPoint po = GetPivotPosition();
	iPoint pos(po.x, po.y);
	SDL_Rect section = { 2285, 799, 29, 29 };
	sprite = new Sprite(tex, pos, sprite_pivot, section);
	App->render->AddSpriteToList(sprite);
}

//NOTE: this is totally, absolutely provisional
void itmPotionHP::Effect()
{
	j1Player* player = App->game->player;
	player->RestoreHP(HP_points);
}