#pragma once
#include <memory>
#include <vector>
#include "Agent.h"

using std::vector;
using std::shared_ptr;

namespace Agents
{
	class AgentController final
	{
	public:
		inline AgentController() {}
		void UpdateAgents();
		template<typename AgentType = Agent>
		Agent* CreateNewAgent();
	private:
		vector<AgentPtr> m_agents{};
	};

	template<typename AgentType>
	inline Agent* AgentController::CreateNewAgent()
	{
		Agent* agent = new AgentType();
		m_agents.push_back(AgentPtr{ agent });
		return agent;
	}
}