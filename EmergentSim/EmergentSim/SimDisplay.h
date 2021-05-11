#pragma once
#include <SDL.h>
#include <string>
#include "SDL_Logger.h"
#include "Sandbox.h"
#include "IEventObserver.h"
#include "PauseButton.h"
#include "Camera.h"
#include <string>

struct SimDisplaySettings {
	std::string windowTitle;
	int windowWidth;
	int windowHeight;
	SDL_Color backgroundColor;
	SDL_Color agentColor;
	SDL_Color resourceColor;
	SDL_Color wallColor;
};

class SimDisplay : public IEventObserver
{
public:
	SimDisplay(SimDisplaySettings settings, Sandbox& sim);
	~SimDisplay();
	bool Update();
	void Handle(SDL_Event& e);

private:
	SimDisplaySettings m_settings;
	Camera m_cam;

	Sandbox& m_sandbox;

	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
	SDL_Renderer* m_renderer;

	PauseButton* m_pauseButton;

	SDL_Logger m_logger;
	
	float m_gridWidthToPixels = 1.0f;
	const int m_defaultWidthToPixels = 40;
	const int m_minGridPixelSize = 10;

	void SetColor(SDL_Color);
	void DrawEntities();
	void DrawEntity(Entity* entity, float scale = 0.75f);
	void DrawGrid();
	void DrawUI();
	void HandleScroll(SDL_MouseWheelEvent& e);
	void ScrollZoomOut();
	void ScrollZoomIn();

};

