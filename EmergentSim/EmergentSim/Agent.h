#pragma once
#include <memory>
#include <vector>
#include "Behavior.h"
#include "EventInfo.h"
#include "Entity.h"
#include "Event.h"
#include "Reaction.h"

using std::vector;
using std::shared_ptr;

namespace Agents
{
	class Agent : public Entity
	{
	public:
		Agent(Transform transform = Transform{ 0, 0, Transform::Direction::DOWN }, SDL_Color color = { 214, 115, 13, 255 }) noexcept;
		virtual void ProcessEvents(vector<EventInfo> events);

		inline virtual EntityType GetType()
		{
			return EntityType::AGENT;
		}
	protected:
		ReactionPtr GetReaction(int eventId);

		vector<ReactionPtr> m_reactions{};
		ReactionPtr m_idle{};
	};

	// type alias for smart pointer
	using AgentPtr = shared_ptr<Agent>;
}