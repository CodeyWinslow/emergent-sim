#pragma once
#include "Button.h"

namespace EmergentGraphics
{
	class PauseButton : public Button
	{
	public:
		PauseButton(SDL_Renderer* renderer, SDL_Rect bounds,
			SDL_Color playColor = { 28,212,98,255 }, SDL_Color pauseColor = { 250,87,117,255 });
		void OnButtonClicked();

	private:
		SDL_Color m_playColor;
		SDL_Color m_pauseColor;
	};

}