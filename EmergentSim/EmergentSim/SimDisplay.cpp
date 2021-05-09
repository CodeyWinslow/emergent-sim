#include "SimDisplay.h"
#include "SDL_Exception.h"

SimDisplay::SimDisplay(Sandbox& sandbox, std::string windowTitle, int windowWidth, int windowHeight) : m_sandbox(sandbox), m_window(nullptr), m_screenSurface(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		const std::string msg = "Failed to initialize";
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg);
	}

	m_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		const std::string msg = "Window could not be created!";
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg + std::string(SDL_GetError()));
	}

	m_screenSurface = SDL_GetWindowSurface(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	//UNSAFE FOR LINUX ??
	//SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(m_window);
}

SimDisplay::~SimDisplay()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool SimDisplay::Update()
{
	SDL_RenderClear(m_renderer);

	DrawEntities();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_WINDOWEVENT_CLOSE:
				event.type = SDL_QUIT;
				SDL_PushEvent(&event);
				break;
			case SDL_QUIT:
				return false;
				break;
		}
	}

	SDL_RenderPresent(m_renderer);
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

void SimDisplay::DrawEntity(const Entity* entity, float scale)
{
	if (entity == nullptr)
		return;

	int gridSquare = m_defaultWidthToPixels * m_gridWidthToPixels;

	int wh = gridSquare * scale;

	int offset = (gridSquare - wh) / 2;

	SDL_Rect rect = { entity->x*gridSquare + offset, entity->y * gridSquare + offset, wh, wh};

	SDL_Color prevCol;
	SDL_GetRenderDrawColor(m_renderer, &prevCol.r, &prevCol.g, &prevCol.b, &prevCol.a);
	SDL_SetRenderDrawColor(m_renderer, 255, 165, 0, 255);
	if (SDL_RenderFillRect(m_renderer, &rect) != 0)
		m_logger.SDL_LogError(std::cout, "Failed to render rect");
	SDL_SetRenderDrawColor(m_renderer, prevCol.r, prevCol.g, prevCol.b, prevCol.a);
	//SDL_FillRect(m_screenSurface, &rect, SDL_MapRGB(m_screenSurface->format, entity->color.r, entity->color.g, entity->color.b));
}