#include "IdleReaction.h"

#include <ctime>
#include <random>
#include "MoveForwardAction.h"
#include "TurnAction.h"

using namespace Agents;

IdleReaction::IdleReaction() noexcept 
	: Reaction{}
{
	srand((unsigned int)time(NULL));

	// make a list of possible behaviors
	vector<ActionPtr> actions =
	{
		ActionPtr{ new MoveForwardAction{1} }
	};
	Behavior moveForward{ actions };

	actions =
	{
		ActionPtr{ new TurnAction{1} }
	};
	Behavior turnRight{ actions };

	actions =
	{
		ActionPtr{ new TurnAction{-1} }
	};
	Behavior turnLeft{ actions };

	// apply our behaviors to our reaction
	m_behaviors =
	{
		moveForward, turnLeft, turnRight
	};
}

void Agents::IdleReaction::React(EntityPtr me, EntityPtr other)
{
	// generate a number between 1 and 6
	int behaviorIndex = (std::rand() % 6) + 1;

	if (behaviorIndex < 4)
	{
		if (behaviorIndex % 2) behaviorIndex = 1;
		else behaviorIndex = 2;
	}
	else behaviorIndex = 0;

	m_behaviors[behaviorIndex].Execute(me, other);
}
