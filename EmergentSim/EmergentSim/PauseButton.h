#pragma once

#include <string>
#include "ImageButton.h"

namespace EmergentGraphics
{
	class PauseButton : public ImageButton
	{
	public:
		PauseButton(SDL_Renderer* renderer, SDL_Rect bounds, std::string imageFileName = "res/img/pause.png",
			SDL_Color playColor = { 28,212,98,165 }, SDL_Color pauseColor = { 250,87,117,255 });
		void OnButtonClicked();

	private:
		SDL_Color m_playColor;
		SDL_Color m_pauseColor;
	};

}