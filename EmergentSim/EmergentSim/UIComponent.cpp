#include "UIComponent.h"

using namespace EmergentGraphics;

UIComponent::UIComponent(SDL_Renderer* renderer, SDL_Rect bounds) :
	m_renderer(renderer), m_bounds(bounds)
{}

UIComponent::~UIComponent() {}