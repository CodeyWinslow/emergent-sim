#pragma once

#include "Action.h"

namespace Agents
{
	class MoveForwardAction final : public Action
	{
	public:
		inline MoveForwardAction(int numCells) noexcept
			: m_numCells(numCells)
		{

		}

		//****************************************
		// Move an entity forward
		//****************************************
		bool _Execute(EntityPtr entity) override;
	private:
		int m_numCells{};
	};
}