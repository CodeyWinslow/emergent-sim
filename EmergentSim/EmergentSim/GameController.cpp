#include "GameController.h"
#include "InputManager.h"

GameController::GameController(int numberAgents, int agentDelay, int sandboxWidth, int sandboxHeight, SimDisplaySettings windowSettings) :
	m_sandbox(sandboxWidth, sandboxHeight), m_agentController(),
	m_playing(true), m_numAgents(numberAgents), m_agentDelay(agentDelay),
	m_camTarget(nullptr)
{
	m_instance = this;
	InitializeAgents(numberAgents);

	m_display = new SimDisplay(windowSettings, m_sandbox);
	InputManager::GetInstance().SubscribeEvent(InputEvent::BUTTON_DOWN, this);
}

GameController::~GameController()
{
	InputManager::GetInstance().UnsubscribeEvent(InputEvent::BUTTON_DOWN, this);
	delete m_display;
}

GameController* GameController::m_instance = nullptr;

GameController& GameController::GetInstance()
{
	return *m_instance;
}

void GameController::Start()
{
	int willUpdate = m_agentDelay;
	while (true)
	{
		if (m_camTarget.get() != nullptr)
			m_display->GetCamera()->Focus(m_camTarget->GetTransform());

		if (!m_display->Update())
			return;

		if (m_playing)
		{
			if (willUpdate <= 0)
			{
				m_agentController.UpdateAgents();
				willUpdate = m_agentDelay;
			}
			else willUpdate--;
		}
	}
}

void GameController::Pause()
{
	m_playing = false;
}

void GameController::Resume()
{
	m_playing = true;
}

void GameController::Restart()
{
	int sbWidth = m_sandbox.GetWidth();
	int sbHeight = m_sandbox.GetHeight();
	m_sandbox = Sandbox(sbWidth, sbHeight);
	m_agentController = AgentController();
	InitializeAgents(m_numAgents);
	m_camTarget = EntityPtr{ nullptr };
}

void GameController::Untarget()
{
	m_camTarget = EntityPtr{ nullptr };
}

void GameController::InitializeAgents(int numberAgents)
{
	for (int ii = 0; ii < numberAgents; ++ii)
	{
		EntityPtr agent{ m_agentController.CreateNewAgent() };
		m_sandbox.RandomlyPlaceEntity(agent);
	}
}

void GameController::Handle(SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			if (m_display->GetUI().IsHovering())
				return;

			SDL_Rect mousePos;
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			Transform worldPos = m_display->GetCamera()->CameraToWorld(mousePos);
			if (worldPos.x >= 0 && worldPos.x < m_sandbox.GetWidth()
				&& worldPos.y >= 0 && worldPos.y < m_sandbox.GetHeight())
			{
				EntityPtr clicked = m_sandbox.GetEntity(worldPos.x, worldPos.y);
				if (clicked != nullptr)
					m_camTarget = clicked;
			}
		}
		break;
	}
}
