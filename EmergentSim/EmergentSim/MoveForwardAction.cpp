#include "MoveForwardAction.h"
#include "GameController.h"

using namespace Agents;

bool MoveForwardAction::_Execute(Entity* entity)
{
	Sandbox* sandbox = GameController::GetInstance().GetSandbox();

	Transform destination = entity->GetTransform();
	destination.Forward(m_numCells);

	sandbox->MoveEntity(entity, destination);
	return true;
}