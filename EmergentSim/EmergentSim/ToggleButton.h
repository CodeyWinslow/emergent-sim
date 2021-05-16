#pragma once
#include "Button.h"

namespace EmergentGraphics
{
    class ToggleButton :
        public Button
    {
    public:
        ToggleButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color offColor, SDL_Color onColor);

        //synchronize on/off status of button with some source
        virtual void SyncState();

    protected:
        SDL_Color m_onColor;
        SDL_Color m_offColor;
    };
}

