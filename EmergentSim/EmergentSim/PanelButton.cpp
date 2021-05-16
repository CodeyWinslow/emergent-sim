#include "PanelButton.h"

EmergentGraphics::PanelButton::PanelButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color backColor, std::function<void()> onClick) :
	Button::Button(renderer, bounds, backColor), m_onClick(onClick)
{}

void EmergentGraphics::PanelButton::OnButtonClicked()
{
	m_onClick();
}
