#include "Button.h"

using namespace EmergentGraphics;

Button::Button(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color backColor) :
	UIComponent::UIComponent(renderer, bounds),
	m_buttonPressed(false), m_backColor(backColor)
{
	InputManager::GetInstance().SubscribeEvent(InputEvent::BUTTON_DOWN, this);
	InputManager::GetInstance().SubscribeEvent(InputEvent::BUTTON_UP, this);
}

Button::~Button()
{
	InputManager::GetInstance().UnsubscribeEvent(InputEvent::BUTTON_DOWN, this);
	InputManager::GetInstance().UnsubscribeEvent(InputEvent::BUTTON_UP, this);
}

void Button::SetBackColor(SDL_Color color)
{
	m_backColor = color;
}

void Button::Render() const
{
	if (m_renderer == nullptr)
		return;

	SDL_SetRenderDrawColor(m_renderer, m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
	SDL_RenderFillRect(m_renderer, &m_bounds);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 165);
	SDL_RenderDrawLine(m_renderer, m_bounds.x, m_bounds.y, m_bounds.x + m_bounds.w, m_bounds.y);
	SDL_RenderDrawLine(m_renderer, m_bounds.x + m_bounds.w, m_bounds.y, m_bounds.x + m_bounds.w, m_bounds.y + m_bounds.h);
	SDL_RenderDrawLine(m_renderer, m_bounds.x, m_bounds.y + m_bounds.h, m_bounds.x + m_bounds.w, m_bounds.y + m_bounds.h);
	SDL_RenderDrawLine(m_renderer, m_bounds.x, m_bounds.y, m_bounds.x, m_bounds.y + m_bounds.h);
}

void Button::HandleButtonDown(SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		SDL_Point clickPoint{ e.x, e.y };

		if (SDL_PointInRect(&clickPoint, &m_bounds))
		{
			m_buttonPressed = true;
		}
	}
}

void Button::HandleButtonUp(SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		SDL_Point clickPoint{ e.x, e.y };

		if (SDL_PointInRect(&clickPoint, &m_bounds))
		{
			if (m_buttonPressed)
			{
				m_buttonPressed = false;
				OnButtonClicked();
			}
		}
		else
		{
			m_buttonPressed = false;
		}
	}
}

void Button::Handle(SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			HandleButtonDown(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			HandleButtonUp(e.button);
			break;
	}
}

