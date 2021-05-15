#include "ConsumeResourceAction.h"
#include "GameController.h"

using namespace Agents;

bool ConsumeResourceAction::_Execute(EntityPtr entity)
{
	Sandbox* s = GameController::GetInstance().GetSandbox();

	Transform transform = entity->GetTransform();
	transform.Forward(1);

	const EntityPtr other = s->At(transform);
	if (other.get() == nullptr) return false;

	s->RemoveEntity(other);

	return true;
}