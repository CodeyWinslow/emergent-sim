#include "Behavior.h"

using namespace Agents;

bool Behavior::_Execute(Entity* me, const Entity* other)
{
	for (ActionPtr& action : m_actions)
		if (!action->Execute(me)) return false;
	return true;
}