#pragma once
#include "UIComponentPanel.h"

namespace EmergentGraphics
{
    class UIComponentFloodPanel :
        public UIComponentPanel
    {
    public:
        UIComponentFloodPanel(SDL_Renderer* renderer, SDL_Point position,
            SDL_Point padding = {}, SDL_Point buttonMargin = { 10,0 },
            SDL_Color backColor = { 214, 161, 107, 220 });

    protected:
        virtual void ResizePanelAroundComponents();
        virtual void PanelButtonClicked() override;
    };
}