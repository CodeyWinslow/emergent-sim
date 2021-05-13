#include "ResetButton.h"
#include "GameController.h"

ResetButton::ResetButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color backColor, std::string fileName) :
	ImageButton::ImageButton(renderer, fileName, bounds, backColor)
{}

void ResetButton::OnButtonClicked()
{
	GameController::GetInstance().Restart();
}
