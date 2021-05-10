#include "Agent.h"
#include "Reaction.h"
#include "IdleReaction.h"

using namespace Agents;

Agent::Agent(Transform transform) noexcept
	: Entity(transform), m_idle{ new IdleReaction{} }
{
	// set up default reactions
	
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
	if (events.size() > 0)
	{
		for (EventInfo& event : events)
		{
			reaction = GetReaction(event.event);
			if (reaction == nullptr)
				continue;

			reaction->React(this, event.entity);
		}
	}
	else
	{
		// perform the idle action
		m_idle->React(this, nullptr);
	}
}