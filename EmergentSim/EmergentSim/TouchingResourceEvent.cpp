#include "TouchingResourceEvent.h"
#include "GameController.h"
#include "EventCodes.h"

using namespace Agents;

TouchingResourceEvent::TouchingResourceEvent() noexcept
	: Event(Events::TouchingResource)
{

}

vector<EventInfo> TouchingResourceEvent::Poll(Entity* me, vector<Entity*> entities)
{
	vector<EventInfo> events{};

	Sandbox* s = GameController::GetInstance().GetSandbox();

	Transform transform = me->GetTransform();
	transform.Forward(1);

	const Entity* entity = s->At(transform);
	if (entity != nullptr && entity->GetType() == EntityType::RESOURCE)
	{
		EventInfo info{ GetId(), entity };
		events.push_back(info);
	}

	return events;
}