#pragma once
#include "Button.h"
class PauseButton : public Button
{
public:
	PauseButton(SDL_Rect bounds, SDL_Color backColor = {20,20,20,255});
	void OnButtonClicked();
};

