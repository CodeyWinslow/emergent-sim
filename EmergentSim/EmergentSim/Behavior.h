#pragma once
#include "Action.h"
#include <vector>

using std::vector;

class Behavior
{
public:
	Behavior();
	~Behavior();

	void AddAction(Action& action);

private:
	vector<Action> m_actions;
};