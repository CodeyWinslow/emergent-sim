#include "DefaultSimDisplay.h"
#include "PauseButton.h"
#include "ResetButton.h"
#include "ToolsPanel.h"

using namespace EmergentGraphics;

DefaultSimDisplay::DefaultSimDisplay(SDL_Renderer* renderer, SDL_Rect bounds) :
	UICanvas::UICanvas(renderer, bounds)
{

	AddComponent(new PauseButton(m_renderer,
			{ bounds.w - 58,
			bounds.h - 58,
			48,48
			}));

	AddComponent(new ResetButton(m_renderer,
			{ bounds.w- 58, 10, 48, 48 }));

	//AddComponent(new UIComponentPanel(m_renderer, { 10,10,200, bounds.h - 100 }));
	//AddComponent(new UIComponentFloodPanel(m_renderer, { 10,10 }, { 40,20 }, {5,0}, { 214, 161, 107, 220 }));
	AddComponent(new ToolsPanel(m_renderer));
}