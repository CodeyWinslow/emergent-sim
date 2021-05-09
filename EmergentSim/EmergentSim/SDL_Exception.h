#pragma once
#include <string>

class SDL_Exception
{
public:
	SDL_Exception(std::string message)
	{
		m_message = message;
	}

private:
	std::string m_message;
};