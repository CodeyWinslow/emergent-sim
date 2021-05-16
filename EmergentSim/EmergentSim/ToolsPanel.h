#pragma once
#include "UICanvas.h"
#include "Button.h"

namespace EmergentGraphics
{
    class ToolsPanel :
        public UICanvas
    {
    public:
        ToolsPanel(SDL_Renderer* renderer, SDL_Rect openedBounds, SDL_Rect closedBounds, SDL_Color backColor = { 214, 161, 107, 220 });
        ~ToolsPanel();

        virtual void Render() const override;
        virtual bool IsHovering() const override;

    protected:
        bool m_opened = true;

        SDL_Rect m_openedBounds;
        SDL_Rect m_closedBounds;
        Button* m_openButton;
        Button* m_closeButton;

        SDL_Color m_backColor;

        virtual void PanelButtonClicked();
    };
}

