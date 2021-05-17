#pragma once

#include <string>
#include "Button.h"
#include "ButtonImage.h"
#include "SDL_image.h"

namespace EmergentGraphics
{
    class ImageButton :
        public Button
    {
    public:
        ImageButton(SDL_Renderer* renderer, std::string imageFileName, SDL_Rect bounds, SDL_Color backColor);
        virtual ~ImageButton();

        virtual void Render() const;
    protected:
        SDL_Texture* m_imageTexture;
    };

}