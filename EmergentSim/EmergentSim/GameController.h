#pragma once
#include "Sandbox.h"
#include "AgentController.h"
#include "SimDisplay.h"

using namespace Agents;
using namespace EmergentGraphics;

class GameController : public IEventObserver
{
public:
	GameController(int numberAgents, int agentDelay, int sandboxWidth, int sandboxHeight, SimDisplaySettings windowSettings);
	~GameController();

	static GameController& GetInstance();

	void Start();
	void Pause();
	void Resume();
	void Restart();

	// Inherited via IEventObserver
	virtual void Handle(SDL_Event& e) override;

	void Untarget();

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

	Entity* m_camTarget;

	void InitializeAgents(int numberAgents);

};