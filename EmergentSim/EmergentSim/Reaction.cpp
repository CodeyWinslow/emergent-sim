#include "Reaction.h"

#include <ctime>
#include <random>
#include "Entity.h"

using namespace Agents;

void Reaction::React(EntityPtr me, EntityPtr other)
{
	if (m_behaviors.empty()) return;

	int behaviorIndex = std::rand() % m_behaviors.size();
	m_behaviors[behaviorIndex].Execute(me, other);
}