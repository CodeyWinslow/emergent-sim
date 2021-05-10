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
		ActionPtr{ new MoveForwardAction{-1} }
	};
	Behavior moveBackward{ actions };

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
		moveForward, moveBackward, turnLeft, turnRight
	};
}