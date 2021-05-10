#include "PauseButton.h"
#include <iostream>
PauseButton::PauseButton(SDL_Rect bounds, SDL_Color backColor) : Button::Button(bounds, backColor)
{}
void PauseButton::OnButtonClicked()
{
	std::cout << "Button clicked!" << std::endl;
}
