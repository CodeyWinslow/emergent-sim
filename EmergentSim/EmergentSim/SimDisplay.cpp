#include "SimDisplay.h"
#include "SDL_Exception.h"

SimDisplay::SimDisplay(Sandbox& sandbox, std::string windowTitle, int windowWidth, int windowHeight) : m_sandbox(sandbox), m_window(nullptr), m_screenSurface(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw SDL_Exception("Failed to initialize");
	}

	m_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		throw SDL_Exception("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
	}

	m_screenSurface = SDL_GetWindowSurface(m_window);

	SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(m_window);
}

SimDisplay::~SimDisplay()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool SimDisplay::Update()
{
	DrawEntities();
	SDL_Delay(1000 / 60);
	return true;
}

void SimDisplay::DrawEntities()
{
	int height = m_sandbox.GetHeight();
	int width = m_sandbox.GetWidth();
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			DrawEntity(m_sandbox[x][y]);
		}
	}
}

void SimDisplay::DrawEntity(Entity* entity)
{

}