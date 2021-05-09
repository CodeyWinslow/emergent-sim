#pragma once
#include <SDL.h>
#include <string>

class Entity {};
class Sandbox {
public:
	int GetWidth() { return 0; }
	int GetHeight() { return 0; }
	Entity** operator[] (int index) { return nullptr; }
};

class SimDisplay
{
public:
	SimDisplay(Sandbox& sim, std::string windowTitle, int windowWidth, int windowHeight);
	~SimDisplay();
	bool Update();

private:
	Sandbox& m_sandbox;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;

	SDL_Logger m_logger;

	float m_gridWidthToPixels = 1.0f;
	const int m_defaultWidthToPixels = 20;

	void DrawEntities();
	void DrawEntity(Entity* entity);
};

