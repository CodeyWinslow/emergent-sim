#pragma once

#include "Event.h"

namespace Agents
{
	class ResourceNearEvent : public Event
	{
	public:
		ResourceNearEvent() noexcept;
		virtual vector<EventInfo> Poll(EntityPtr me, vector<EntityPtr> entities) override;
	private:
		
	};
}