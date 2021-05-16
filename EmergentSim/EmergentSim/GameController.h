#pragma once

#include "Sandbox.h"
#include "AgentController.h"
#include "SimDisplay.h"
#include "Toolbox.h"

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
	void Untarget();
	inline bool IsPlaying() { return m_playing; }
	inline Tool GetCurrentTool() { return m_currentTool; }
	inline void SetCurrentTool(Tool tool) { m_currentTool = tool; }

	inline Sandbox* GetSandbox() { return &m_sandbox; }

	virtual void Handle(SDL_Event& e) override;

private:
	static GameController* m_instance;

	bool m_playing;
	int m_numAgents;
	int m_agentDelay;

	EntityPtr m_camTarget;
	Tool m_currentTool = Tool::NONE;

	Sandbox m_sandbox;
	AgentController m_agentController;
	SimDisplay* m_display;

	void InitializeAgents(int numberAgents);
};