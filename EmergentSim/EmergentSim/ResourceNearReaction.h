#pragma once

#include "Reaction.h"

namespace Agents
{
	class ResourceNearReaction : public Reaction
	{
	public:
		ResourceNearReaction() noexcept;

		//****************************************
		// Move toward the food
		//****************************************
		void React(Entity* me, const Entity* other) override;
	private:

	};
}