#include <vector>
#include "Agent.h"
#include "AgentController.h"
#include "ActionMove.h"
#include "ActionTurn.h"
#include "EventInfo.h"
#include <random>

using std::vector;

Agent::Agent()
	: Entity(), m_reactions()
{
	Reaction idle;
	Behavior idleBehavior;

	const int NUM_ACTIONS = 2;
	const int NUM_AGENT_ACTIONS = 3;
	static vector<Action> ACTION_LIST = { ActionMove{}, ActionTurn{} };

	for (int ii = 0; ii < NUM_AGENT_ACTIONS; ++ii)
	{
		idleBehavior.AddAction(ACTION_LIST[std::rand() % NUM_ACTIONS]);
	}

	idle.AddBehavior(idleBehavior);
}

Agent::Agent(AgentController* controller, Transform transform, int lifespan, int maxHunger)
	: Entity(transform), m_hunger(maxHunger), m_maxHunger(maxHunger), m_life(lifespan), m_lifespan(lifespan), m_controller(controller)
{
}

Agent::~Agent()
{
}


void Agent::ProcessEvents(vector<EventInfo> events)
{
	if (events.size() == 0)
	{
		// Do IDLE reaction
		EventInfoPtr result = m_controller->RequestBehavior(this, m_reactions.at(0).GetBehavior());
		if (result != nullptr)
		{
			// Collided, carry out interaction logic
			Interact(result);
		}
	}
	else
	{
		throw new std::exception("We got an event????");
	}
}

void Agent::Interact(EventInfoPtr eventInfo)
{
	// Stop actions, so just do nothing for now
}