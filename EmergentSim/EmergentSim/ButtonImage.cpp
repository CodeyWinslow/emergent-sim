#include "ButtonImage.h"

EmergentGraphics::ButtonImage::ButtonImage(SDL_Renderer* renderer, std::string imageFileName, SDL_Rect bounds) :
	UIComponent::UIComponent(renderer, bounds)
{
	m_imageTexture = IMG_LoadTexture(renderer, imageFileName.c_str());
	if (m_imageTexture == nullptr)
		throw FileException("Failed to open file: " + imageFileName);
}

EmergentGraphics::ButtonImage::~ButtonImage()
{
	if (m_imageTexture != nullptr)
		SDL_DestroyTexture(m_imageTexture);
}

void EmergentGraphics::ButtonImage::Render() const
{
	if (m_renderer == nullptr || !m_enabled)
		return;

	SDL_RenderCopy(m_renderer, m_imageTexture, nullptr, &m_bounds);
}
