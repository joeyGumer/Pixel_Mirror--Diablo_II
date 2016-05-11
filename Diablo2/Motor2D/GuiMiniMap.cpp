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
;
GuiMiniMap::GuiMiniMap(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list, SDL_Texture* texMapa) : GuiElement(p, r, GUI_MINIMAP, par, list)
{
	texMapa = App->tex->Load("maps/mini_path.png");
	
}

GuiMiniMap::~GuiMiniMap()
{

}


void GuiMiniMap::Draw()
{
	//image.Draw();

	//print map
	if (tex != NULL)
		App->render->Blit(tex, rect.x - App->render->camera.x, rect.y - App->render->camera.y);

	//print units
	if (active_entities != NULL)
	{
		for (std::map<uint, Entity*>::iterator it = active_entities->begin(); it != active_entities->end(); ++it)
		{
			Entity* entity = it->second;

			// Set drawing quad for each unit
			// Choose quad color
			/*Uint8 r, g, b;
			switch (entity->faction)
			{
			case FACTION::PLAYER:
			r = 0;
			g = 0;
			b = 255;
			break;

			case FACTION::COMPUTER:
			r = 255;
			g = 0;
			b = 0;
			break;*/

			//}

			// send to render
			//iPoint quad_pos = worldToMinimap({ (int)entity->center.x, (int)entity->center.y });
			//app->render->DrawQuad({ quad_pos.x, quad_pos.y, 1, 1 }, r, g, b);
		}
	}

	// print area
	iPoint pos = worldToMinimap({ -App->render->camera.x, -App->render->camera.y });
	App->render->DrawQuad({ pos.x, pos.y, area.w, area.h }, 255, 255, 255, 255, false);


}

void GuiMiniMap::Update(GuiElement* hover, GuiElement* focus)
{
	// check if using GuiMinimap
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint mouse_pos;
		mouse_pos = App->input->GetMousePosition();
		LOG("click mouse capturada la posicio del ratoli. ");
		if (mouse_pos.x < rect.x + rect.w && mouse_pos.x > rect.x && mouse_pos.y < rect.y + rect.h && mouse_pos.y > rect.y)
			App->render->CenterCamera(mouse_pos.x, mouse_pos.y);
		LOG("entra al segon if centre la camera al update. ");
	}
}

bool GuiMiniMap::SetAttributes(map<uint, Entity*>* entities, SDL_Texture* texture)
{
	bool ret = true;

	if (ret = (entities != NULL))
		active_entities = entities;

	if (ret && (ret = (texture != NULL)))
		tex = texture;

	//set scale
	calculateScale();



	return ret;
}


void GuiMiniMap::calculateScale()
{
	scale.x = rect.w / (float)(App->map->data.width * App->map->data.tile_width);    //map width
	scale.y = rect.h / (float)(App->map->data.height * App->map->data.tile_height);  //map height;

	area.w = App->render->camera.w * scale.x;
	area.h = App->render->camera.h * scale.y;
}

iPoint GuiMiniMap::minimapToWorld(const iPoint &mini_map_pos) const
{
	iPoint world_pos;
	world_pos.x = mini_map_pos.x / scale.x;
	world_pos.y = mini_map_pos.y / scale.y;

	// The method will never return the exact corners as world positions.
	if (world_pos.x <= (App->render->camera.w / 2))
		world_pos.x = App->render->camera.w / 2;
	else if (world_pos.x >= (App->map->data.tile_width * App->map->data.width) - (App->render->camera.w / 2))
		world_pos.x = (App->map->data.tile_width * App->map->data.width) - (App->render->camera.w / 2);

	if (world_pos.y <= (App->render->camera.h / 2))
		world_pos.y = App->render->camera.h / 2;
	else if (world_pos.y >= (App->map->data.tile_height * App->map->data.height) - (App->render->camera.h / 2))
		world_pos.y = (App->map->data.tile_height * App->map->data.height) - (App->render->camera.h / 2);

	return world_pos;
}

iPoint GuiMiniMap::worldToMinimap(const iPoint &world_pos) const
{
	iPoint mini_map_pos;

	mini_map_pos.x = rect.x + (world_pos.x * scale.x) - App->render->camera.x;
	mini_map_pos.y = rect.y + (world_pos.y * scale.y) - App->render->camera.y;

	return mini_map_pos;
}

