#include "SimDisplay.h"
#include "SDL_Exception.h"
#include "SDL_image.h"
#include "DefaultSimDisplay.h"
#include "InputManager.h"

using namespace EmergentGraphics;

SimDisplay::SimDisplay(SimDisplaySettings settings, Sandbox& sandbox) :
	m_sandbox(sandbox), m_window(nullptr),
	m_cam(nullptr, settings.windowWidth, settings.windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || IMG_Init(IMG_INIT_PNG) == 0) {
		const std::string extras = std::string(SDL_GetError());
		const std::string msg = "Failed to initialize: " + extras;
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg);
	}

	SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "1");

	m_settings = settings;
	m_window = SDL_CreateWindow(settings.windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings.windowWidth, settings.windowHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		const std::string msg = "Window could not be created!";
		m_logger.SDL_LogError(std::cout, msg);
		throw SDL_Exception(msg + std::string(SDL_GetError()));
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	m_cam.SetRenderer(m_renderer);
	m_entityShader = new ShrinkShader(0.8f);
	m_cam.ApplyShader(m_entityShader);

	SetColor(settings.backgroundColor);

	SDL_UpdateWindowSurface(m_window);

	m_ui = new DefaultSimDisplay(m_renderer, { 0,0,settings.windowWidth, settings.windowHeight });

	SubscribeToInput();
}

SimDisplay::~SimDisplay()
{
	UnsubscribeToInput();

	delete m_ui;

	m_cam.RemoveShader(m_entityShader);

	SDL_DestroyWindow(m_window);
	IMG_Quit();
	SDL_Quit();
}

bool SimDisplay::Update()
{
	if (m_quit)
		return false;

	InputManager::GetInstance().Update();

	SetColor(m_settings.backgroundColor);
	SDL_RenderClear(m_renderer);

	DrawEntities();

	DrawUI();

	SDL_UpdateWindowSurface(m_window);
	SDL_RenderPresent(m_renderer);
	SDL_Delay(1000 / 60);

	return true;
}

void SimDisplay::Handle(SDL_Event& e)
{
	switch (e.type)
	{
		case SDL_WINDOWEVENT_CLOSE:
		case SDL_QUIT:
			m_quit = true;
	}
}

Camera* SimDisplay::GetCamera()
{
	return &m_cam;
}

const Camera* SimDisplay::GetCamera() const
{
	return &m_cam;
}

UIComponent& const EmergentGraphics::SimDisplay::GetUI() const
{
	return *(m_ui);
}

void SimDisplay::SubscribeToInput()
{
	InputManager::GetInstance().SubscribeEvent(InputEvent::QUIT, this);
}

void SimDisplay::UnsubscribeToInput()
{
	InputManager::GetInstance().UnsubscribeEvent(InputEvent::QUIT, this);
}

void SimDisplay::SetColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
}

void SimDisplay::DrawEntities()
{
	Transform minBounds = m_cam.GetMinBounds();
	Transform maxBounds = m_cam.GetMaxBounds();
	int sbHeight = m_sandbox.GetHeight();
	int sbWidth = m_sandbox.GetWidth();

	int beginX = (minBounds.x) < 0 ? 0 : minBounds.x;
	int beginY = (minBounds.y) < 0 ? 0 : minBounds.y;
	int endX = (maxBounds.x) > sbHeight ? sbWidth : maxBounds.x;
	int endY = (maxBounds.y) > sbHeight ? sbHeight : maxBounds.y;

	for (int x = beginX; x < endX; ++x)
	{
		for (int y = beginY; y < endY; ++y)
		{
			const EntityPtr entity = m_sandbox.GetEntity(x, y);
			if (entity) entity->Draw(&m_cam);
		}
	}
}

void SimDisplay::DrawGrid() {

	Transform line(0, 0, Transform::Direction::UP);
	SDL_Rect linePos;

	//don't render if too small
	if (m_cam.WorldToCamera(line).w < m_minGridPixelSize)
		return;

	SetColor({ 0,0,0,255 });
	
	int column_lines = m_sandbox.GetWidth() + 1;
	int row_lines = m_sandbox.GetHeight() + 1;

	for(int ii = 0; ii < column_lines; ii++) {
		line.x = ii;
		linePos = m_cam.WorldToCamera(line, 1, m_sandbox.GetHeight());
		SDL_RenderDrawLine(m_renderer, linePos.x, linePos.y, linePos.x, linePos.y + linePos.h);
	}

	line.x = 0;

	for(int ii = 0; ii < row_lines; ii++) {
		line.y = ii;
		linePos = m_cam.WorldToCamera(line, m_sandbox.GetWidth(), 1);
		SDL_RenderDrawLine(m_renderer, linePos.x, linePos.y, linePos.x+ linePos.w, linePos.y);
	}

}

void SimDisplay::DrawUI()
{
	m_ui->Render();
}