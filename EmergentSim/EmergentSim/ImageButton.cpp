#include "ImageButton.h"

ImageButton::ImageButton(SDL_Renderer* renderer, std::string imageFileName, SDL_Rect bounds, SDL_Color backColor) :
	Button::Button(renderer, bounds, backColor)
{
	m_imageTexture = IMG_LoadTexture(m_renderer, imageFileName.c_str());
	if (m_imageTexture == nullptr)
		throw FileException("Failed to open file: " + imageFileName);
	SDL_SetTextureBlendMode(m_imageTexture, SDL_BLENDMODE_BLEND);
}

ImageButton::~ImageButton()
{
	if (m_imageTexture != nullptr)
 		SDL_DestroyTexture(m_imageTexture);
}

void ImageButton::Render()
{
	if (m_renderer == nullptr)
		return;

	Button::Render();

	SDL_RenderCopy(m_renderer, m_imageTexture, nullptr, &m_buttonBounds);
}
