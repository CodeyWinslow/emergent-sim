#pragma once

#include "Event.h"

class Entity;

namespace Agents
{
	class TouchingResourceEvent : public Event
	{
	public:
		TouchingResourceEvent() noexcept;
		virtual vector<EventInfo> Poll(Entity* me, vector<Entity*> entities) override;
	private:

	};
}