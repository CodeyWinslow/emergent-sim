#include "Agent.h"

using namespace Agents;

Agent::Agent(Transform transform) noexcept
	: Entity(transform)
{

}

ReactionPtr Agent::GetReaction(Event* event)
{
	unsigned int eventId = event->GetId();
	if (eventId >= m_reactions.size())
		return ReactionPtr{ nullptr };

	return m_reactions[eventId];
}

void Agent::ProcessEvents(vector<EventInfo> events)
{
	ReactionPtr reaction;

	for (EventInfo& event : events)
	{
		reaction = GetReaction(event.event);
		if (reaction == nullptr)
			continue;

		reaction->React(this, event.entity);
	}
}