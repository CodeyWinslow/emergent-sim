#pragma once
#include "Action.h"
#include "Agent.h"

class ActionMove :
    public Action
{
public:
    shared_ptr<EventInfo> Execute(Agent* agent, Environment* environment);
};

