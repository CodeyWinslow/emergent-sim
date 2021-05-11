#pragma once
#include "Camera.h"

class IRenderable
{
public:
	virtual void Draw(Camera* camera) = 0;
};