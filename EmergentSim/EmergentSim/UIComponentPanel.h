#pragma once
#include "UICanvas.h"
#include "Button.h"
#include "ButtonImage.h"

namespace EmergentGraphics
{
    class UIComponentPanel :
        public UICanvas
    {
    public:
        UIComponentPanel(SDL_Renderer* renderer, SDL_Rect bounds,
            SDL_Point padding = {}, SDL_Point buttonMargin = {10,0},
            SDL_Color backColor = { 214, 161, 107, 220 });
        virtual ~UIComponentPanel();

        virtual void Render() const override;
        virtual bool IsHovering() const override;

    protected:
        const std::string m_openButtonFilePath = "res/img/plus.png";
        const std::string m_closeButtonFilePath = "res/img/minus.png";

        bool m_opened = true;

        SDL_Point m_padding;
        SDL_Point m_buttonMargin;

        SDL_Color m_backColor;

        //SDL_Rect m_closedBounds;
        Button* m_openButton;
        Button* m_closeButton;
        ButtonImage* m_openButtonImage;
        ButtonImage* m_closeButtonImage;

        virtual void PanelButtonClicked();
    };
}

