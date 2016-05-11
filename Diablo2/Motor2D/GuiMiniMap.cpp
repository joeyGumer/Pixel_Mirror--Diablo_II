#include "GuiMiniMap.h"

;
GuiMiniMap::GuiMiniMap(iPoint p, SDL_Rect r, GuiElement* par, j1Module* list) : GuiElement(p, r, GUI_MINIMAP, par, list), image({ 0, 0 }, r, this, NULL)
{

}

GuiMiniMap::~GuiMiniMap()
{

}


void GuiMiniMap::Draw()
{
	image.Draw();
}

void GuiMiniMap::Update(GuiElement* hover, GuiElement* focus)
{

}