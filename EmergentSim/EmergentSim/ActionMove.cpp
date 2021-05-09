#include "ActionMove.h"
#include "EventInfo.h"

shared_ptr<EventInfo> ActionMove::Execute(Agent* agent, Environment* environment)
{
    shared_ptr<EventInfo> retVal{ new EventInfo{} };

    Transform nextTile = agent->GetTransform();
    nextTile.Forward(1);

    Entity* target = environment->GetEntity(nextTile);

    // If nothing is there, we can just move normally so move and return nullptr
    if (target == nullptr)
    {
        // Move
        environment.MoveEntity(agent, nextTile);

        // Set retVal to nullptr
        retVal = nullptr;
    }
    else
        retVal->SetEntity(target);

    return retVal;
}
