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
		Agent* CreateNewAgent();
	private:
		vector<AgentPtr> m_agents{};
		vector<EventPtr> m_events{};
	};

	template<typename AgentType>
	inline Agent* AgentController::CreateNewAgent()
	{
		Agent* agent = new AgentType();
		m_agents.push_back(AgentPtr{ agent });
		return agent;
	}
}