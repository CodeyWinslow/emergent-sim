#pragma once
#include "Action.h"

namespace Agents
{
	class ConsumeResourceAction : public Action
	{
	public:

	private:
		bool _Execute(Entity* entity) override;
	};
}