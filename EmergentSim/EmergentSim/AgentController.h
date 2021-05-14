#pragma once
#include <memory>
#include <vector>
#include "Agent.h"

using std::vector;
using std::shared_ptr;

namespace Agents
{
	class Event;

	class AgentController final
	{
	public:
		AgentController() noexcept;
		void UpdateAgents();
		template<typename AgentType = Agent>
		EntityPtr CreateNewAgent();
	private:
		vector<EntityPtr> m_agents{};
		vector<EventPtr> m_events{};
	};

	template<typename AgentType>
	inline EntityPtr AgentController::CreateNewAgent()
	{
		EntityPtr agent = EntityPtr{ new AgentType() };
		m_agents.push_back(agent);
		return agent;
	}
}