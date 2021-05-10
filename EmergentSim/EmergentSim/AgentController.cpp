#include "AgentController.h"
#include "Agent.h"

using namespace Agents;

AgentController::AgentController() noexcept
{

}

void AgentController::UpdateAgents()
{
	for (AgentPtr& agent : m_agents)
	{
		vector<EventInfo> events{};

		// gather list of events for this agent

		agent->ProcessEvents(events);
	}
}