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
		inline Behavior(vector<ActionPtr> actions) noexcept : m_actions{ actions } {}
		inline ~Behavior() noexcept { m_actions.clear(); }

		//****************************************
		// IOC to execute behavior with guarantee
		// of nullptr safety
		//****************************************
		inline bool Execute(EntityPtr me, const EntityPtr other)
		{
			runtime_assert(me.get() != nullptr);
			return _Execute(me, other);
		}
	protected:
		//****************************************
		// me is guaranteed not to be nullptr,
		// other may be nullptr
		//****************************************
		virtual bool _Execute(EntityPtr me, const EntityPtr other);

		vector<ActionPtr> m_actions{};
	};
}