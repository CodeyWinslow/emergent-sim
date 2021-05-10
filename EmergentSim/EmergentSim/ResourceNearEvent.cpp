#include "ResourceNearEvent.h"
#include "EventCodes.h"

using namespace Agents;

ResourceNearEvent::ResourceNearEvent() noexcept
	: Event(Events::NearResource)
{

}

vector<EventInfo> ResourceNearEvent::Poll(Entity* me, vector<Entity*> entities)
{
	vector<EventInfo> events{};

	Entity* other{ nullptr };
	float dist = 10;
	Transform myTransform = me->GetTransform();

	for (Entity* entity : entities)
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

	if (other != nullptr)
	{
		EventInfo e{ GetId(), other };
		events.push_back(e);
	}

	return events;
}