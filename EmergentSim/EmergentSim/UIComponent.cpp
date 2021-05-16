#include "UIComponent.h"

using namespace EmergentGraphics;

UIComponent::UIComponent(SDL_Renderer* renderer, SDL_Rect bounds) :
	m_renderer(renderer), m_bounds(bounds)
{}

UIComponent::~UIComponent() {}

bool EmergentGraphics::UIComponent::IsHovering() const
{
	if (!m_enabled)
		return false;

	SDL_Point mousePosition;
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	return SDL_PointInRect(&mousePosition, &m_bounds);
}
