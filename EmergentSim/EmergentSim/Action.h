#pragma once
#include "EventInfo.h"

class Action
{
public:
	virtual EventInfoPtr Execute(Agent* agent, Environment* environment) = 0;
};