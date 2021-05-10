#include "GameController.h"

GameController::GameController(int numberAgents, int sandboxWidth, int sandboxHeight, SimDisplaySettings windowSettings) :
	m_sandbox(sandboxWidth, sandboxHeight), m_agentController(), m_playing(true)
{
	m_instance = this;
	InitializeAgents(numberAgents);

	m_display = new SimDisplay(windowSettings, m_sandbox);
}

GameController::~GameController()
{
	delete m_display;
}

GameController* GameController::m_instance = nullptr;

GameController* GameController::GetInstance()
{
	return m_instance;
}

void GameController::Start()
{
	while (true)
	{
		if (!m_display->Update())
			return;

		if (m_playing)
			m_agentController.UpdateAgents();
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

void GameController::InitializeAgents(int numberAgents)
{
	for (int ii = 0; ii < numberAgents; ++ii)
	{
		Agent* agent = m_agentController.CreateNewAgent();
		m_sandbox.RandomlyPlaceEntity(agent);
	}
}
