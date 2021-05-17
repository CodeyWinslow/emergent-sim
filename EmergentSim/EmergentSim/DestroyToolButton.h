#pragma once
#include "ToggleButton.h"
#include "GameController.h"
#include "ButtonImage.h"

namespace EmergentGraphics
{
    class DestroyToolButton :
        public ToggleButton
    {
    public:
        DestroyToolButton(SDL_Renderer* renderer, SDL_Rect bounds,
            SDL_Color offColor = { 250,87,117,255 }, SDL_Color onColor = { 28,212,98,165 });

        virtual void Render() const override;

        virtual void SetBounds(SDL_Rect bounds) override;

        virtual void SyncState() override;

        virtual void OnButtonClicked() override;
    private:
        const std::string m_imageFilePath = "res/img/trash.png";
        GameController& m_gameInstance;
        ButtonImage m_image;
    };
}

