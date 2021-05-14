#include "Agent.h"
#include "Reaction.h"
#include "IdleReaction.h"
#include "ConsumeResourceReaction.h"
#include "ResourceNearReaction.h"
#include "Event.h"

#pragma warning(disable : 4244)

using namespace Agents;

Agent::Agent(Transform transform, SDL_Color color) noexcept
	: Entity(transform, color), m_idle{ new IdleReaction{} }
{
	// set up default reactions
	m_reactions =
	{
		ReactionPtr{ new ConsumeResourceReaction{} },
		ReactionPtr{ new ResourceNearReaction{} }
	};
}

void Agents::Agent::Draw(Camera* cam)
{
	Entity::Draw(cam);

	SDL_Rect face = cam->WorldToCamera(m_transform);
	SDL_Rect original = face;
	switch (m_transform.direction)
	{
	case Transform::Direction::UP:
		face.w *= 0.8f;
		face.h *= 0.2f;
		face.x += (original.w - face.w) / 2;
		face.y += face.h;
		break;
	case Transform::Direction::DOWN:
		face.w *= 0.8f;
		face.h *= 0.2f;
		face.x += (original.w - face.w) / 2;
		face.y += original.h - (2 * face.h);
		break;
	case Transform::Direction::LEFT:
		face.w *= 0.2f;
		face.h *= 0.8f;
		face.x += face.w;
		face.y += (original.h - face.h) / 2;
		break;
	case Transform::Direction::RIGHT:
		face.w *= 0.2f;
		face.h *= 0.8f;
		face.x += original.w - (2 * face.w);
		face.y += (original.h - face.h) / 2;
		break;
	}

	SDL_Color col = { 0,0,0,50 };
	cam->Draw(face, col);
}

ReactionPtr Agent::GetReaction(int eventId)
{
	if (eventId >= m_reactions.size())
		return ReactionPtr{ nullptr };

	return m_reactions[eventId];
}

void Agent::ProcessEvents(AgentPtr me, vector<EventInfo> events)
{
	ReactionPtr reaction;
	if (events.size() > 0)
	{
		for (EventInfo& event : events)
		{
			reaction = me->GetReaction(event.id);
			if (reaction.get() == nullptr)
				continue;

			reaction->React(me, event.entity);
		}
	}
	else
	{
		// perform the idle action
		me->m_idle->React(me, EntityPtr{ nullptr });
	}
}