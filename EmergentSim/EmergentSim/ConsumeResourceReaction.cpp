#include "ConsumeResourceReaction.h"
#include <vector>
#include "ConsumeResourceAction.h"

using std::vector;

using namespace Agents;

ConsumeResourceReaction::ConsumeResourceReaction() noexcept
{
	// make a list of possible behaviors
	vector<ActionPtr> actions =
	{
		ActionPtr{ new ConsumeResourceAction{} }
	};
	Behavior consume{ actions };

	m_behaviors =
	{
		consume
	};
}