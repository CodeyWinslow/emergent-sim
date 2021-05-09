#pragma once

class EventInfoPtr;

class Event
{
public:
	virtual EventInfoPtr CheckForEvent(Agent* agent, Environment* environment) = 0;
};