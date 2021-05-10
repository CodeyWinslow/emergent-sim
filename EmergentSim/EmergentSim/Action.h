#pragma once
#include <memory>
#include "Entity.h"
#include "runtime_assert.h"

namespace Agents
{
	class Action
	{
	public:
		inline Action() noexcept {}

		//****************************************
		// IOC to execute action with guarantee
		// of nullptr safety
		//****************************************
		inline bool Execute(Entity* entity)
		{
			// throws an assertion failure if entity is ever nullptr
			runtime_assert(entity != nullptr);
			return _Execute(entity);
		}
	protected:
		//****************************************
		// entity is guaranteed not to be nullptr
		//****************************************
		virtual bool _Execute(Entity* entity) = 0;
	};

	using ActionPtr = std::shared_ptr<Action>;
}