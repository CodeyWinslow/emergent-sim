#include "MoveForwardAction.h"
#include "GameController.h"

using namespace Agents;

bool MoveForwardAction::_Execute(EntityPtr entity)
{
	Sandbox* sandbox = GameController::GetInstance().GetSandbox();

	Transform destination = entity->GetTransform();
	destination.Forward(m_numCells);
	return sandbox->MoveEntity(entity, destination);
}