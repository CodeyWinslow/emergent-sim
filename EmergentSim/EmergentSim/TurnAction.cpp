#include "TurnAction.h"
#include "GameController.h"

using namespace Agents;

bool TurnAction::_Execute(Entity* entity)
{
	Sandbox* sandbox = GameController::GetInstance().GetSandbox();

	Transform destination = entity->GetTransform();
	destination.Turn(m_numTimes);

	sandbox->MoveEntity(entity, destination);
	return true;
}