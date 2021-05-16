#include "ToggleButton.h"

EmergentGraphics::ToggleButton::ToggleButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color offColor, SDL_Color onColor) :
	Button::Button(renderer, bounds, offColor), m_onColor(onColor), m_offColor(offColor)
{
	SyncState();
}

void EmergentGraphics::ToggleButton::SyncState()
{
}
