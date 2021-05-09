#pragma once
#include "Action.h"
#include "Agent.h"

class ActionTurn :
    public Action
{
public:
    EventInfoPtr Execute(Agent* agent, Environment* environment);
};

