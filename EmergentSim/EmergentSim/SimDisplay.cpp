#include <string>
#include "SimDisplay.h"
#include "SDL_Exception.h"

SimDisplay::SimDisplay(SimContainer& sim, std::string windowTitle, int windowWidth, int windowHeight) : m_sim(sim), m_window(nullptr), m_screenSurface(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw SDL_Exception("Failed to initialize");
	}

	m_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		throw SDL_Exception("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}

	m_screenSurface = SDL_GetWindowSurface(m_window);

	SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(m_window);
}

SimDisplay::~SimDisplay()
{
	SDL_Quit();
}

bool SimDisplay::Update()
{
	int sandboxSize = m_sim.GetSandboxSize();
	int sandboxWidth = m_sim.GetSandboxWidth();
	Entity * sandbox = m_sim.GetSandbox();

	DrawEntities(sandbox, sandboxSize, sandboxWidth);
}

void SimDisplay::DrawEntities(Entity* sandbox, int length, int width)
{
	m_sim.VisitEntities(SimDisplay::DrawEntity);
}

void SimDisplay::DrawEntity(Entity* entity)
{

}