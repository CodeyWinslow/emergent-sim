#pragma once
#include <vector>
#include "Action.h"

using std::vector;

namespace Agents
{
	class Behavior
	{
	public:
		inline Behavior() noexcept {}
		inline ~Behavior() noexcept { m_actions.clear(); }

		//****************************************
		// IOC to execute behavior with guarantee
		// of nullptr safety
		//****************************************
		inline bool Execute(Entity* me, Entity* other)
		{
			runtime_assert(me != nullptr);
			return _Execute(me, other);
		}
	protected:
		//****************************************
		// me is guaranteed not to be nullptr
		//****************************************
		virtual bool _Execute(Entity* me, Entity* other);

		vector<ActionPtr> m_actions{};
	};
}