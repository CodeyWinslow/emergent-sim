#pragma once

#include <vector>
#include "Entity.h"

using std::vector;

namespace Agents
{
	struct EventInfo final
	{
		inline EventInfo(unsigned int id, EntityPtr entity)
			: id(id), entity(entity) {}

		unsigned int id;
		EntityPtr entity;
	};
}