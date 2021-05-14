#pragma once

#pragma region includes
#include <SDL.h>
#include <string>

#include "SDL_Logger.h"
#include "Sandbox.h"

//rendering
#include "Camera.h"
#include "ShrinkShader.h"

#include "IEventObserver.h"

//UI
#include "UICanvas.h"

#include <string>
#pragma endregion

namespace EmergentGraphics
{

	struct SimDisplaySettings {
		std::string windowTitle;
		int windowWidth{};
		int windowHeight{};
		SDL_Color backgroundColor{};
	};

	class SimDisplay : public IEventObserver
	{
	public:
		SimDisplay(SimDisplaySettings settings, Sandbox& sim);
		~SimDisplay();
		bool Update();
		void Handle(SDL_Event& e);
		Camera* GetCamera();

	private:
		//settings
		bool m_quit = false;
		SimDisplaySettings m_settings;
		float m_gridWidthToPixels = 1.0f;
		const int m_defaultWidthToPixels = 40;
		const int m_minGridPixelSize = 10;

		//game-specific
		Sandbox& m_sandbox;

		//Custom rendering
		Camera m_cam;
		Shader* m_entityShader;

		//SDL rendering
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		//UI
		UICanvas* m_ui;

		//Tools
		SDL_Logger m_logger;

		//functions
		void SubscribeToInput();
		void UnsubscribeToInput();
		void SetColor(SDL_Color);
		void DrawEntities();
		void DrawGrid();
		void DrawUI();

	};

}