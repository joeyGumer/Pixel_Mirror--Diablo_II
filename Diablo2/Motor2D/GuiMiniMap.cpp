#include "GuiMiniMap.h"
;
#include "j1App.h"
#include "j1Gui.h"
#include "Entity.h"
#include "p2Log.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1Game.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "p2Point.h"
#include "EntEnemy.h"
#include "j1EntityManager.h"

;
GuiMiniMap::GuiMiniMap(iPoint p, SDL_Rect r, SDL_Texture* tex, GuiElement* par, j1Module* list) : GuiElement(p, r, GUI_MINIMAP, par, list), 
			image(p,r,tex,par,list)
{
	SetAlpha(tex, 90);
	//this->rect = r;
	scale.x = 20;
	scale.y = 20;
	
}

GuiMiniMap::~GuiMiniMap()
{

}


void GuiMiniMap::Draw()
{

	
	image.Draw();

	App->render->DrawQuad({ GetScreenPosition().x - App->render->camera.x, GetScreenPosition().y - App->render->camera.y, 400, 200 }, 255, 255, 255, 255, false);
	DrawPlayer(App->game->player);
//	DrawEnemy(App->game->player->enemy)
	/*
	DrawPlayer(App->game->player);
	

	// print area
	fPoint pos;
	pos.x = App->render->camera.x;
	pos.y = App->render->camera.y;
	pos = WorldToMinimap(pos);
	App->render->DrawQuad({ pos.x, pos.y, 400, 200 }, 255, 255, 255, 255, false);
	*/

}

void GuiMiniMap::Update(GuiElement* hover, GuiElement* focus)
{
	// check if using GuiMinimap
	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint mouse_pos;
		mouse_pos = App->input->GetMousePosition();
		if (mouse_pos.x < image.tex_rect.x + image.tex_rect.w && mouse_pos.x > image.tex_rect.x && mouse_pos.y < image.tex_rect.y + image.tex_rect.h && mouse_pos.y > image.tex_rect.y)
			App->render->setCameraOnPosition(WorldToMinimapi(mouse_pos));
		
	}
	
	
}



void GuiMiniMap::calculateScale()
{
	//scale.x = rect.w / (float)(App->map->data.width * App->map->data.tile_width);    //map width
	//scale.y = rect.h / (float)(App->map->data.height * App->map->data.tile_height);  //map height;

	//area.w = App->render->camera.w * scale.x;
	//area.h = App->render->camera.h * scale.y;
}

iPoint GuiMiniMap::minimapToWorld(const iPoint &mini_map_pos)
{
	SDL_Rect mini_map = image.GetTextureRect();

	float currentX = (mini_map_pos.x - mini_map.x) / (float)mini_map.w;
	float currentY = (mini_map_pos.y - mini_map.y) / (float)mini_map.h;

	currentX = currentX * (App->map->data.width * App->map->data.tile_width);
	currentY = currentY * (App->map->data.height * App->map->data.tile_height);

	return iPoint(currentX, currentY);
}

iPoint GuiMiniMap::WorldToMinimapi(const iPoint &world_pos)
{
	//SDL_Rect mini_map = image.GetTextureRect();
	iPoint mini_pos;

	mini_pos.x = (world_pos.x / scale.x) + App->render->camera.x;
	mini_pos.y = (world_pos.y / scale.y) + App->render->camera.y;


	//currentX = mini_map.x + currentX * mini_map.w;
	//currentY = mini_map.y + currentY * mini_map.h;
	//currentY
	//currentX = mini_map_pos.x + currentX * rect.w;
	//currentY = mini_map_pos.y + currentY * rect.h;
	//return mini_map_pos;
	return mini_pos;
}

fPoint GuiMiniMap::WorldToMinimap(const fPoint &world_pos)
{
	SDL_Rect mini_map = image.GetTextureRect();
	//fPoint mini_pos;

	fPoint mini_pos;

	mini_pos.x = (GetScreenPosition().x - App->render->camera.x) + (world_pos.x / scale.x) + 200;
	mini_pos.y = (GetScreenPosition().y - App->render->camera.y) + (world_pos.y / scale.y);

	//mini_pos.x = GetScreenPosition().x + mini_pos.x;
	//mini_pos.y = GetScreenPosition().y + mini_pos.y;
	//currentX = mini_map.x + currentX * mini_map.w;
	//currentY = mini_map.y + currentY * mini_map.h;
	//currentY
	//currentX = mini_map_pos.x + currentX * rect.w;
	//currentY = mini_map_pos.y + currentY * rect.h;
	//return mini_map_pos;
	return mini_pos;
}


void GuiMiniMap::SetAlpha(SDL_Texture* tex, Uint8 alpha)
{
	SDL_SetTextureAlphaMod(tex, alpha);
}

void GuiMiniMap::DrawPlayer(j1Player* player)
{
	fPoint toDraw = WorldToMinimap(player->GetPivotPosition());
	//fPoint toDraw = minimapToWorld(player->GetPivotPosition());
	if (player->active)
	{
		App->render->DrawQuad(SDL_Rect{ toDraw.x, toDraw.y, 4, 4 }, false, 255, 255, 255, 200);
	}
	
}

void GuiMiniMap::DrawEnemy(EntEnemy* enemy)
{
	fPoint toDraw = WorldToMinimap(enemy->GetPivotPosition());
	//fPoint toDraw = minimapToWorld(player->GetPivotPosition());
	//if (enemy->PlayerInRange())
	//{
		App->render->DrawQuad(SDL_Rect{ toDraw.x, toDraw.y, 2, 2 }, false, 255, 150, 200, 200);
	//}

}
