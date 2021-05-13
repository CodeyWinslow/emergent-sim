#include "DefaultSimDisplay.h"
#include "PauseButton.h"
#include "ResetButton.h"

using namespace EmergentGraphics;

DefaultSimDisplay::DefaultSimDisplay(SDL_Renderer* renderer, SDL_Rect bounds) :
	UICanvas::UICanvas(renderer, bounds)
{

	AddComponent(new PauseButton(m_renderer,
			{ bounds.w - 160,
			bounds.h - 60,
			150,50
			}));

	AddComponent(new ResetButton(m_renderer,
			{ bounds.w- 58, 10, 48, 48 }));
}