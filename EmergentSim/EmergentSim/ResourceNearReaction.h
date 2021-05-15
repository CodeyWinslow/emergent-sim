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
		void React(EntityPtr me, const EntityPtr other) override;
	private:

	};
}