#include "TurnAction.h"

using namespace Agents;

bool TurnAction::_Execute(Entity* entity)
{
	// Sandbox* sandbox = GameController::GetSandbox();

	Transform destination = entity->GetTransform();
	destination.Turn(m_numTimes);

	// sandbox->MoveEntity(entity, destination);
	return true;
}