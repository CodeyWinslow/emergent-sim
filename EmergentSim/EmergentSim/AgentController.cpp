#include "AgentController.h"
#include "EventInfo.h"

AgentController::AgentController(vector<Event&> events, Environment* environment)
	: m_events(events), m_environment(environment)
{
}

AgentController::~AgentController()
{
}

void AgentController::Update()
{
	vector<EventInfo> eventResponses;
	for (Agent* agent : m_agents)
	{
		for (Event& e : m_events)
		{
			EventInfoPtr response = e.CheckForEvent(agent, m_environment);
			if(response.get() != nullptr)
				eventResponses.push_back(*(response.get()));
		}

		agent->ProcessEvents(eventResponses);

		eventResponses.clear();
	}
}

/******************************************************************************
	Returns nullptr if the behavior was carried out.
	Returns an EventInfoPtr if the behavior was NOT carried out, implying a collision.
******************************************************************************/
EventInfoPtr AgentController::RequestBehavior(Agent* agent, Behavior behavior)
{
	for (Action* action : behavior.GetActions())
	{
		EventInfoPtr result = action.Execute(agent, m_environment);
		if (result != nullptr)
			return result;
	}
	return nullptr;
}
