#pragma once
#include <SDL.h>

class SimContainer;
class Entity;

class SimDisplay
{
public:
	SimDisplay(SimContainer& sim, std::string windowTitle, int windowWidth, int windowHeight);
	~SimDisplay();
	bool Update();

private:
	SimContainer& m_sim;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;

	SDL_Logger m_logger;

	float m_gridWidthToPixels = 1.0f;
	const int m_defaultWidthToPixels = 20;

	void DrawEntities(Entity* sandbox, int length, int width);
	void DrawEntity(Entity* entity);
};

