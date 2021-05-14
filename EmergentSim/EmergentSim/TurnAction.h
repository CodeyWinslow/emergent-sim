#pragma once

#include "Action.h"

namespace Agents
{
	class TurnAction final : public Action
	{
	public:
		inline TurnAction(int numTimes) noexcept
			: m_numTimes(numTimes)
		{

		}

		//****************************************
		// Turn an entity a number of times
		//****************************************
		bool _Execute(EntityPtr entity) override;
	private:
		int m_numTimes{};
	};
}