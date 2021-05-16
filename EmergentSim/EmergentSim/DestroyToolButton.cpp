#include "DestroyToolButton.h"

EmergentGraphics::DestroyToolButton::DestroyToolButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color offColor, SDL_Color onColor) :
	ToggleButton::ToggleButton(renderer, bounds, offColor, onColor), m_gameInstance(GameController::GetInstance())
{}

void EmergentGraphics::DestroyToolButton::SyncState()
{
	if (m_gameInstance.GetCurrentTool() == Tool::DESTROY_ENTITY)
		SetBackColor(m_onColor);
	else
		SetBackColor(m_offColor);
}

void EmergentGraphics::DestroyToolButton::OnButtonClicked()
{
	if (m_gameInstance.GetCurrentTool() == Tool::DESTROY_ENTITY)
		m_gameInstance.SetCurrentTool(Tool::NONE);
	else
		m_gameInstance.SetCurrentTool(Tool::DESTROY_ENTITY);

	SyncState();
}


