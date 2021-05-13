#pragma once
#include "Shader.h"

namespace EmergentGraphics
{
    class ShrinkShader :
        public Shader
    {
    public:
        ShrinkShader(float scale);
        SDL_Rect Compute(SDL_Rect rect);

    private:
        float m_scale;
    };

}