#include "ActionTurn.h"

EventInfo ActionTurn::Execute(Agent* agent, Environment* environment)
{
    EventInfo retVal;

    Transform nextTile = agent.GetTransform();
    nextTile.forward(1);
    retVal.SetEntity(environment.GetEntity(nextTile));

    return retVal;
}
