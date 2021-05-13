#include "PauseButton.h"

#include <iostream>
#include "GameController.h"

using namespace EmergentGraphics;

PauseButton::PauseButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color playColor, SDL_Color pauseColor) :
	Button::Button(renderer, bounds, playColor), m_playColor(playColor), m_pauseColor(pauseColor)
{}

void PauseButton::OnButtonClicked()
{
	GameController& game = GameController::GetInstance();

	if (!game.IsPlaying())
	{
		game.Resume();
		SetBackColor(m_playColor);
	}
	else
	{
		game.Pause();
		SetBackColor(m_pauseColor);
	}
}
