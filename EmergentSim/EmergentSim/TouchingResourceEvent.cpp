#include "TouchingResourceEvent.h"
#include "GameController.h"
#include "EventCodes.h"

using namespace Agents;

TouchingResourceEvent::TouchingResourceEvent() noexcept
	: Event(Events::TouchingResource)
{

}

vector<EventInfo> TouchingResourceEvent::Poll(EntityPtr me, vector<EntityPtr> entities)
{
	vector<EventInfo> events{};

	Sandbox* s = GameController::GetInstance().GetSandbox();

	Transform transform = me->GetTransform();
	transform.Forward(1);

	const EntityPtr entity = s->At(transform);
	if (entity.get() != nullptr && entity->GetType() == EntityType::RESOURCE)
	{
		EventInfo info{ GetId(), entity };
		events.push_back(info);
	}

	return events;
}