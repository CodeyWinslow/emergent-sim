#include "ResourceNearReaction.h"
#include "MoveForwardAction.h"
#include "TurnAction.h"

#include <cmath>

using namespace Agents;

ResourceNearReaction::ResourceNearReaction() noexcept
{
	vector<ActionPtr> actions{};

	m_behaviors =
	{

	};
}

void ResourceNearReaction::React(Entity* me, Entity* other)
{
	Transform myTransform = me->GetTransform();
	Transform theirTransform = other->GetTransform();

	float xDist = abs(myTransform.x - theirTransform.x);
	float yDist = abs(myTransform.y - theirTransform.y);

	// possible states:
	// xDist == 0
		// turn toward it
		// go straight
	// yDist == 0
		// turn toward it
		// go straight
	// xDist < yDist
		// face left or right
		// move until xDist == 0
	// xDist > yDist
		// face up or down
		// move until yDist == 0

	if (xDist == 0)
	{
		// if we need to be facing down
		if (myTransform.y < theirTransform.y)
		{
			if (myTransform.direction != Transform::Direction::DOWN)
			{
				if (myTransform.direction == Transform::Direction::LEFT)
					TurnAction(-1).Execute(me);
				else
					TurnAction(1).Execute(me);
			}
			else
				MoveForwardAction(1).Execute(me);
		}
		else
		{
			if (myTransform.direction != Transform::Direction::UP)
			{
				if (myTransform.direction == Transform::Direction::LEFT)
					TurnAction(1).Execute(me);
				else
					TurnAction(-1).Execute(me);
			}
			else
				MoveForwardAction(1).Execute(me);
		}
	}
	else if (yDist == 0)
	{
		// if we need to be facing right
		if (myTransform.x < theirTransform.x)
		{
			if (myTransform.direction != Transform::Direction::RIGHT)
			{
				if (myTransform.direction == Transform::Direction::DOWN)
					TurnAction(-1).Execute(me);
				else
					TurnAction(1).Execute(me);
			}
			else
				MoveForwardAction(1).Execute(me);
		}
		else
		{
			if (myTransform.direction != Transform::Direction::LEFT)
			{
				if (myTransform.direction == Transform::Direction::DOWN)
					TurnAction(1).Execute(me);
				else
					TurnAction(-1).Execute(me);
			}
			else
				MoveForwardAction(1).Execute(me);
		}
	}
	else
	{
		for (int ii{ 0 }; ii < 4 && !MoveForwardAction(1).Execute(me); ++ii)
		{
			TurnAction(1).Execute(me);
		}
	}
}