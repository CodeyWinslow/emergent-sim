#include "ToolsPanel.h"
#include "ResetButton.h"
#include "DestroyToolButton.h"

EmergentGraphics::ToolsPanel::ToolsPanel(SDL_Renderer* renderer, SDL_Point position,
	SDL_Point padding, SDL_Point buttonMargin, SDL_Color backColor) :
	UIComponentFloodPanel::UIComponentFloodPanel(renderer, position, padding, buttonMargin, backColor)
{
	AddComponent(new DestroyToolButton(renderer, { 0,0,48,48 }));
	//AddComponent(new ResetButton(renderer, { 0,0,48,48 }));
	AddComponent(new ResetButton(renderer, { 0,0,96,96 }));
	AddComponent(new ResetButton(renderer, {0,0,48,48}));
	ResizePanelAroundComponents();
}
