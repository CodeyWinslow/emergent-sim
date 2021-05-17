#include "DestroyToolButton.h"

EmergentGraphics::DestroyToolButton::DestroyToolButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color offColor, SDL_Color onColor) :
	ToggleButton::ToggleButton(renderer, bounds, offColor, onColor), m_gameInstance(GameController::GetInstance()),
	m_image(renderer, m_imageFilePath, bounds)
{}

void EmergentGraphics::DestroyToolButton::Render() const
{
	ToggleButton::Render();
	m_image.Render();
}

void EmergentGraphics::DestroyToolButton::SetBounds(SDL_Rect bounds)
{
	ToggleButton::SetBounds(bounds);
	m_image.SetBounds(bounds);
}

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


