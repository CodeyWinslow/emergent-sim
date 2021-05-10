#include "Reaction.h"

#include <ctime>
#include <random>
#include "Entity.h"

using namespace Agents;

void Reaction::React(Entity* me, Entity* other)
{
	if (m_behaviors.empty()) return;

	//std::srand((unsigned int)std::time(NULL));
	int behaviorIndex = std::rand() % m_behaviors.size();
	m_behaviors[behaviorIndex].Execute(me, other);
}