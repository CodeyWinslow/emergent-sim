#include "SimDisplay.h"
#include "SDL_Exception.h"

SimDisplay::SimDisplay(SimDisplaySettings settings, Sandbox& sandbox) : 
	m_sandbox(sandbox), m_window(nullptr), m_screenSurface(nullptr),
	m_cam()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		const std::string msg = "Failed to initialize";
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg);
	}

	m_settings = settings;
	m_window = SDL_CreateWindow(settings.windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings.windowWidth, settings.windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		const std::string msg = "Window could not be created!";
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg + std::string(SDL_GetError()));
	}

	m_screenSurface = SDL_GetWindowSurface(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SetColor(settings.backgroundColor);

	//UNSAFE FOR LINUX ??
	//SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(m_window);
	//InputManager::GetInstance().SubscribeEvent(InputEvent::SCROLL, this);
	//InputManager::GetInstance().SubscribeEvent(InputEvent::BUTTON_DOWN, this);
	//InputManager::GetInstance().SubscribeEvent(InputEvent::BUTTON_UP, this);
	m_pauseButton = new PauseButton({
		settings.windowWidth - 160,
		settings.windowHeight - 60,
		150,50
		});
}

SimDisplay::~SimDisplay()
{
	delete m_pauseButton;
	//InputManager::GetInstance().UnsubscribeEvent(InputEvent::SCROLL, this);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool SimDisplay::Update()
{
	SetColor(m_settings.backgroundColor);
	SDL_RenderClear(m_renderer);

	if (!InputManager::GetInstance().Update())
		return false;

	DrawGrid();
	DrawEntities();

	DrawUI();

	SDL_RenderPresent(m_renderer);
	SDL_Delay(1000 / 60);
	return true;
}

void SimDisplay::Handle(SDL_Event& e)
{
	//handle multiple events with switch
	SDL_MouseWheelEvent* wh = &e.wheel;
	HandleScroll(*wh);
}

void SimDisplay::SetColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

void SimDisplay::DrawEntities()
{
	int height = m_sandbox.GetHeight();
	int width = m_sandbox.GetWidth();
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			DrawEntity(m_sandbox.GetEntity(x,y));
		}
	}
}

void SimDisplay::DrawEntity(Entity* entity, float scale)
{
	if (entity == nullptr)
		return;

	if (entity->GetType() == EntityType::WALL)
		SetColor(m_settings.wallColor);
	else if (entity->GetType() == EntityType::RESOURCE)
		SetColor(m_settings.resourceColor);
	else if (entity->GetType() == EntityType::AGENT)
		SetColor(m_settings.agentColor);

	SDL_Rect screenPos = m_cam.WorldToCamera(entity->GetTransform());
	int scaledWidth = screenPos.w * scale;
	int offset = (screenPos.w - scaledWidth) / 2;
	screenPos.x += offset;
	screenPos.y += offset;
	screenPos.w = screenPos.h = scaledWidth;
	if (SDL_RenderFillRect(m_renderer, &screenPos) != 0)
		m_logger.SDL_LogError(std::cout, "Failed to render rect");
}

void SimDisplay::DrawGrid() {

	int column_lines = m_sandbox.GetWidth() + 1;
	int row_lines = m_sandbox.GetHeight() + 1;
	int gridSquare = m_defaultWidthToPixels * m_gridWidthToPixels;

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	
	for(int ii = 0; ii < column_lines; ii++) {
		Transform col(ii, 0, Transform::Direction::UP);
		SDL_Rect screenPos = m_cam.WorldToCamera(col, 1, m_sandbox.GetHeight());
		SDL_RenderDrawLine(m_renderer, screenPos.x, screenPos.y, screenPos.x, screenPos.y + screenPos.h);
		//SDL_RenderDrawLine(m_renderer, ii*gridSquare, 0, ii*gridSquare, m_sandbox.GetHeight()*gridSquare);
	}

	for(int ii = 0; ii < row_lines; ii++) {
		Transform col(0,ii, Transform::Direction::UP);
		SDL_Rect screenPos = m_cam.WorldToCamera(col, m_sandbox.GetWidth(), 1);
		SDL_RenderDrawLine(m_renderer, screenPos.x, screenPos.y, screenPos.x+screenPos.w, screenPos.y);
		//SDL_RenderDrawLine(m_renderer, 0, ii*gridSquare, m_sandbox.GetWidth()*gridSquare, ii*gridSquare);
	}

}

void SimDisplay::DrawUI()
{
	m_pauseButton->Render(m_renderer);
}

void SimDisplay::HandleScroll(SDL_MouseWheelEvent& e)
{
	if (e.y > 0)
		ScrollZoomIn();
	else
		ScrollZoomOut();
}

void SimDisplay::ScrollZoomOut()
{
	m_gridWidthToPixels -= 0.1f;
	if (m_gridWidthToPixels < 0.1f) m_gridWidthToPixels = 0.1f;
}

void SimDisplay::ScrollZoomIn()
{
	m_gridWidthToPixels += 0.1f;
	if (m_gridWidthToPixels > 8.0f) m_gridWidthToPixels = 8.0f;
}