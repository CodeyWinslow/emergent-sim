#include "Button.h"

Button::Button(SDL_Rect bounds, SDL_Color backColor) : m_buttonPressed(false), m_buttonBounds(bounds), m_backColor(backColor)
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

void Button::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, m_backColor.r, m_backColor.g, m_backColor.b, m_backColor.a);
	SDL_RenderFillRect(renderer, &m_buttonBounds);
}

void Button::HandleButtonDown(SDL_MouseButtonEvent& e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		SDL_Point clickPoint{ e.x, e.y };

		if (SDL_PointInRect(&clickPoint, &m_buttonBounds))
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

		if (SDL_PointInRect(&clickPoint, &m_buttonBounds))
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

