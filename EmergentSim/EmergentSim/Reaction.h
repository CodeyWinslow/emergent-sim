#pragma once
#include <memory>
#include <vector>
#include "Behavior.h"

using std::vector;

class Entity;

namespace Agents
{
	class Reaction
	{
	public:
		inline Reaction() noexcept {}
		inline Reaction(vector<Behavior> behaviors) noexcept
			: m_behaviors{ behaviors } {}

		//**********************************************
		// Selects a random behavior from m_behaviors
		//**********************************************
		virtual void React(Entity* me, Entity* other);
	protected:
		vector<Behavior> m_behaviors{};
	};

	using ReactionPtr = std::shared_ptr<Reaction>;
}