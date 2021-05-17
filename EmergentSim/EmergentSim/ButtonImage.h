#pragma once
#include <string>
#include "UIComponent.h"
#include "SDL_image.h"

namespace EmergentGraphics
{
    class FileException 
    {
    public:
        FileException(std::string message) : m_message(message) {}
        inline std::string GetMessage() { return m_message; }
    private:
        std::string m_message;

    };

    class ButtonImage : public UIComponent
    {
    public:
        ButtonImage(SDL_Renderer* renderer, std::string imageFileName, SDL_Rect bounds);
        virtual ~ButtonImage();

        virtual void Render() const override;

    private:
        SDL_Texture* m_imageTexture;
    };
}