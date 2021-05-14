#pragma once

#include "Event.h"

class Entity;

namespace Agents
{
	class TouchingResourceEvent : public Event
	{
	public:
		TouchingResourceEvent() noexcept;
		virtual vector<EventInfo> Poll(EntityPtr me, vector<EntityPtr> entities) override;
	private:

	};
}