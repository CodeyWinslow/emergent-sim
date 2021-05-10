#pragma once
#include <vector>
#include "Entity.h"
#include "Event.h"

using std::vector;

namespace Agents
{
	struct EventInfo final
	{
		Event* event;
		Entity* entity;
	};
}