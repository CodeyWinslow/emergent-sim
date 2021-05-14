#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
namespace EmergentGraphics
{
    class SDL_Logger {
    private:
    public:
        SDL_Logger();
        ~SDL_Logger();
        void SDL_LogError(std::ostream& os, const std::string& msg);
    };
}