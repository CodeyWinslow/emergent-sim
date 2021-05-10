#pragma once

namespace Agents
{
	class Event
	{
	public:
		inline Event(unsigned int id) noexcept
			: m_id(id) {}

		inline unsigned int GetId() const noexcept
		{
			return m_id;
		}
	protected:
		unsigned int m_id;
	};
}