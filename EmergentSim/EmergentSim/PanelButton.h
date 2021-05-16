#pragma once
#include <functional>
#include "Button.h"

namespace EmergentGraphics
{
    class PanelButton :
        public Button
    {
    public:
        PanelButton(SDL_Renderer* renderer, SDL_Rect bounds, SDL_Color backColor, std::function<void()> onClick);

    private:
        std::function<void()> m_onClick;

        virtual void OnButtonClicked() override;
    };
}

