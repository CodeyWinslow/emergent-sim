#include "PauseButton.h"

#include <iostream>
#include "GameController.h"

PauseButton::PauseButton(SDL_Rect bounds, SDL_Color playColor, SDL_Color pauseColor) :
	Button::Button(bounds, playColor), m_playColor(playColor), m_pauseColor(pauseColor)
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
