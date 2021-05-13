#pragma once
#include "UICanvas.h"

namespace EmergentGraphics
{
	class DefaultSimDisplay : public UICanvas
	{
	public:
		DefaultSimDisplay(SDL_Renderer* renderer, SDL_Rect bounds);
	};
}