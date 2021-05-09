#include "Reaction.h"

Reaction::Reaction()
	: m_behaviors()
{

}

void Reaction::AddBehavior(const Behavior& behavior)
{
	m_behaviors.push_back(behavior);
}

Behavior Reaction::GetBehavior()
{
	return Behavior();
}
