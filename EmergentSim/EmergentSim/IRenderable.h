#pragma once
#include "Camera.h"

namespace EmergentGraphics
{
	class IRenderable
	{
	public:
		virtual void Draw(Camera* camera) = 0;
	};
}