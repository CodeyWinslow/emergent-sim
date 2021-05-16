#pragma once
#include "ToggleButton.h"
#include "GameController.h"

namespace EmergentGraphics
{
    class DestroyToolButton :
        public ToggleButton
    {
    public:
        DestroyToolButton(SDL_Renderer* renderer, SDL_Rect bounds,
            SDL_Color offColor = { 250,87,117,255 }, SDL_Color onColor = { 28,212,98,165 });

        virtual void SyncState() override;

        virtual void OnButtonClicked() override;
    private:
        GameController& m_gameInstance;
    };
}

