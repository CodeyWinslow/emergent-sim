#pragma once
#include <vector>

using std::vector;

class Reaction
{
public:
	Reaction();

	void AddBehavior(Behavior* behavior);

private:
	vector<Behavior*> m_behaviors;
};

