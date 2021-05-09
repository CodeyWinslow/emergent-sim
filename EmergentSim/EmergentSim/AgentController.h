#pragma once
#include <vector>
#include "Event.h"
#include "Agent.h"

using std::vector;

class Environment;

class AgentController
{
public:
	AgentController(vector<Event&> events, Environment* environment);
	~AgentController();

	void Update();
	EventInfoPtr RequestBehavior(Agent* agent, Behavior behavior);
private:
	vector<Event&> m_events;
	vector<Agent*> m_agents;
	Environment* m_environment;
};

