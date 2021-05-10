#pragma once
#include <memory>
#include <vector>
#include "Behavior.h"
#include "EventInfo.h"
#include "Entity.h"
#include "Reaction.h"

using std::vector;
using std::shared_ptr;

namespace Agents
{
	class Agent : public Entity
	{
	public:
		Agent(Transform transform = Transform{ 0, 0, Transform::Direction::DOWN }) noexcept;
		virtual void ProcessEvents(vector<EventInfo> events);

		inline virtual EntityType GetType()
		{
			return EntityType::AGENT;
		}
	protected:
		ReactionPtr GetReaction(Event* event);

		vector<ReactionPtr> m_reactions{};
		ReactionPtr m_idle{};
	};

	// type alias for smart pointer
	using AgentPtr = shared_ptr<Agent>;
}