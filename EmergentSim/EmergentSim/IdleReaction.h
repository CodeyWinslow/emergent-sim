#pragma once

#include "Reaction.h"

namespace Agents
{
	class IdleReaction : public Reaction
	{
	public:
		IdleReaction() noexcept;
		void React(EntityPtr me, EntityPtr other) override;
	private:

	};
}