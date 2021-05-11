#include "ShrinkShader.h"

ShrinkShader::ShrinkShader(float scale) : m_scale(scale)
{}

SDL_Rect ShrinkShader::Compute(SDL_Rect rect)
{
    SDL_Rect scaled;
    scaled.h = rect.h * m_scale;
    scaled.w = rect.w * m_scale;
    scaled.x = rect.x + (rect.w - scaled.w) / 2;
    scaled.y = rect.y + (rect.h - scaled.h) / 2;
    return scaled;
}
