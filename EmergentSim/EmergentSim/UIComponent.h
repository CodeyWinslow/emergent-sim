#pragma once

#include "SDL.h"

namespace EmergentGraphics
{
	class UIComponent
	{
	public:
		UIComponent(SDL_Renderer* renderer, SDL_Rect bounds);
		virtual ~UIComponent();

		inline void SetActive(bool enabled) { m_enabled = enabled; }
		inline virtual SDL_Rect GetBounds() const { return m_bounds; }
		inline virtual void SetBounds(SDL_Rect bounds) { m_bounds = bounds; }

		virtual bool IsHovering() const;

		virtual void Render() const = 0;

	protected:
		bool m_enabled = true;

		SDL_Renderer* m_renderer;
		SDL_Rect m_bounds;
	};
}