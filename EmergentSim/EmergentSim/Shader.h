#pragma once

#include "SDL.h"

namespace EmergentGraphics
{
	class Shader
	{
	public:
		virtual SDL_Rect Compute(SDL_Rect rect) = 0;
	};
}