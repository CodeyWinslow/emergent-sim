#include "ConsumeResourceAction.h"
#include "GameController.h"

using namespace Agents;

bool ConsumeResourceAction::_Execute(Entity* entity)
{
	Sandbox* s = GameController::GetInstance().GetSandbox();

	Transform transform = entity->GetTransform();
	transform.Forward(1);

	const Entity* other = s->At(transform);
	if (other == nullptr) return false;

	s->RemoveEntity(other);

	return true;
}