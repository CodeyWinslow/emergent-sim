#include "UICanvas.h"

using namespace EmergentGraphics;

UICanvas::UICanvas(SDL_Renderer* renderer, SDL_Rect bounds) :
	UIComponent::UIComponent(renderer, bounds)
{}

UICanvas::~UICanvas()
{
	for (UIComponent* component : m_uiComponents)
	{
		delete component;
	}
	m_uiComponents = vector<UIComponent*>();
}

bool EmergentGraphics::UICanvas::IsHovering() const
{
	for (const UIComponent* comp : m_uiComponents)
	{
		if (comp->IsHovering())
			return true;
	}

	return false;
}

void UICanvas::Render() const
{
	for (UIComponent* component : m_uiComponents)
	{
		component->Render();
	}
}

void UICanvas::AddComponent(UIComponent* component)
{
	if (component != nullptr)
		m_uiComponents.push_back(component);
}
