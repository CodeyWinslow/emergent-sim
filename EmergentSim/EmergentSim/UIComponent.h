#pragma once

#include "SDL.h"

namespace EmergentGraphics
{
	class UIComponent
	{
	public:
		UIComponent(SDL_Renderer* renderer, SDL_Rect bounds);
		virtual ~UIComponent();

		virtual void Render() = 0;

	protected:
		SDL_Renderer* m_renderer;
		SDL_Rect m_bounds;
	};
}