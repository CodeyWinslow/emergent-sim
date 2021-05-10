#include "MoveForwardAction.h"

using namespace Agents;

bool MoveForwardAction::_Execute(Entity* entity)
{
	// Sandbox* sandbox = GameController::GetSandbox();

	Transform destination = entity->GetTransform();
	destination.Forward(m_numCells);

	// sandbox->MoveEntity(entity, destination);
	return true;
}