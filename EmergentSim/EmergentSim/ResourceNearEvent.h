#pragma once

#include "Event.h"

namespace Agents
{
	class ResourceNearEvent : public Event
	{
	public:
		ResourceNearEvent() noexcept;
		virtual vector<EventInfo> Poll(Entity* me, vector<Entity*> entities) override;
	private:
		
	};
}