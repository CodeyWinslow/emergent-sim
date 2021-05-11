#pragma once
#include <SDL.h>
#include <string>
#include "SDL_Logger.h"
#include "Sandbox.h"
#include "IEventObserver.h"
#include "PauseButton.h"
#include "Camera.h"
#include "ShrinkShader.h"
#include <string>

struct SimDisplaySettings {
	std::string windowTitle;
	int windowWidth;
	int windowHeight;
	SDL_Color backgroundColor;
};

class SimDisplay : public IEventObserver
{
public:
	SimDisplay(SimDisplaySettings settings, Sandbox& sim);
	~SimDisplay();
	bool Update();
	void Handle(SDL_Event& e);

private:
	bool m_quit = false;
	SimDisplaySettings m_settings;

	Shader* m_entityShader;
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

	void SubscribeToInput();
	void UnsubscribeToInput();
	void SetColor(SDL_Color);
	void DrawEntities();
	//void DrawEntity(Entity* entity, float scale = 0.75f);
	void DrawGrid();
	void DrawUI();

};

