#include "ResourceNearEvent.h"
#include "EventCodes.h"

using namespace Agents;

ResourceNearEvent::ResourceNearEvent() noexcept
	: Event(Events::NearResource)
{

}

vector<EventInfo> ResourceNearEvent::Poll(EntityPtr me, vector<EntityPtr> entities)
{
	vector<EventInfo> events{};

	EntityPtr other{ nullptr };
	float dist = 10;
	Transform myTransform = me->GetTransform();

	for (EntityPtr entity : entities)
	{
		if (entity->GetType() == EntityType::RESOURCE)
		{
			Transform theirTransform = entity->GetTransform();
			float tempDist = myTransform.Distance(theirTransform);
			if (tempDist < dist)
			{
				dist = tempDist;
				other = entity;
			}
		}
	}

	if (other.get() != nullptr)
	{
		EventInfo e{ GetId(), other };
		events.push_back(e);
	}

	return events;
}