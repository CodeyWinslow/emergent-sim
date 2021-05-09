#include "Behavior.h"

Behavior::Behavior()
	: m_actions()
{
}

Behavior::~Behavior()
{
}

void Behavior::AddAction(Action& action)
{
	m_actions.push_back(action);
}
