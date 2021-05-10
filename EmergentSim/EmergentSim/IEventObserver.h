#pragma once
#include "SDL.h"

class IEventObserver
{
public:
	virtual void Handle(SDL_Event& e) = 0;
};