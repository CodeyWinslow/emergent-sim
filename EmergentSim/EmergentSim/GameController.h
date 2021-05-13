#pragma once
#include "Sandbox.h"
#include "AgentController.h"
#include "SimDisplay.h"

using namespace Agents;

class GameController
{
public:
	GameController(int numberAgents, int agentDelay, int sandboxWidth, int sandboxHeight, SimDisplaySettings windowSettings);
	~GameController();

	static GameController& GetInstance();

	void Start();
	void Pause();
	void Resume();
	void Restart();

	inline Sandbox* GetSandbox() { return &m_sandbox; }

	inline bool IsPlaying() { return m_playing; }

private:
	static GameController* m_instance;
	bool m_playing;
	Sandbox m_sandbox;
	AgentController m_agentController;
	int m_numAgents;
	int m_agentDelay;
	SimDisplay* m_display;

	void InitializeAgents(int numberAgents);
};