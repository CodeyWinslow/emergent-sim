#include "SDL_Logger.h"

SDL_Logger::SDL_Logger() { }

SDL_Logger::~SDL_Logger() { }

void SDL_Logger::SDL_LogError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}