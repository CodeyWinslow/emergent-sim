#pragma once
#include <memory>
#include "EventInfo.h"

namespace Agents
{
	class Event
	{
	public:
		inline Event(unsigned int id) noexcept
			: m_id(id) {}

		inline unsigned int GetId() const noexcept
		{
			return m_id;
		}

		virtual vector<EventInfo> Poll(Entity* me, vector<Entity*> entities) = 0;
	protected:
		unsigned int m_id;
	};

	using EventPtr = std::shared_ptr<Event>;
}