#pragma once
#include "ImageButton.h"
class ResetButton :
    public ImageButton
{
public:
    ResetButton(SDL_Renderer* renderer, SDL_Rect bounds = {},
        SDL_Color backColor = { 28,212,98,255 }, std::string fileName = "res/img/reset.png");

    void OnButtonClicked();
};

