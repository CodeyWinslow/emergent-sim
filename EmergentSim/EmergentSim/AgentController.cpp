#include "AgentController.h"
#include "Agent.h"
#include "GameController.h"
#include "TouchingResourceEvent.h"
#include "ResourceNearEvent.h"

using namespace Agents;

AgentController::AgentController() noexcept
{
	m_events =
	{
		EventPtr{ new TouchingResourceEvent{} },
		EventPtr{ new ResourceNearEvent{} }
	};
}

void AgentController::UpdateAgents()
{
	vector<EntityPtr> view{};
	Sandbox* s = GameController::GetInstance().GetSandbox();

	for (EntityPtr& agent : m_agents)
	{
		vector<EventInfo> events{};
		view = s->GetEntitiesInView(agent, 5);

		// gather list of events for this agent
		for (EventPtr e : m_events)
		{
			vector<EventInfo> temp = e->Poll(agent, view);
			for (EventInfo ei : temp)
				events.push_back(ei);
		}

		Agent::ProcessEvents(std::static_pointer_cast<Agent>(agent), events);
	}
}