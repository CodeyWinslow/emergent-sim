#include "AgentController.h"
#include "Agent.h"

using namespace Agents;

void AgentController::UpdateAgents()
{
	for (AgentPtr& agent : m_agents)
	{
		vector<EventInfo> events{};

		// gather list of events for this agent

		agent->ProcessEvents(events);
	}
}