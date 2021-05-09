#pragma once
#include <iostream>
class SDL_Logger {
private:
public:
    SDL_Logger();
    ~SDL_Logger();
	void SDL_LogError(std::ostream &os, const std::string &msg);
};