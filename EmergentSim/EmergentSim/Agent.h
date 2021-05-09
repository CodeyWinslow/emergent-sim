#pragma once
#include <vector>
#include <exception>
#include "Behavior.h"
#include "Reaction.h"
#include "Event.h"
#include "EventInfo.h"
#include "AgentController.h"

using std::vector;

class Entity 
{
public:
	Entity(Transform transform) { m_transform = transform; }
	Entity() {}
	virtual Transform GetTransform() { return m_transform; }
	int GetType() { return 0; }
private:
	Transform m_transform;
};

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Transform
{
public:
	Transform(int x, int y, Direction dir);
	void Forward(int count) {}
private:
	int x, y;
	Direction dir;
};

class Agent : public Entity
{
public:
	Agent();
	Agent(AgentController* controller, Transform transform, int lifespan, int maxHunger);
	~Agent();
	
	void ProcessEvents(vector<EventInfo> events);
	void Interact();

private:
	AgentController* m_controller;
	vector<Reaction> m_reactions;
	
	int m_hunger, m_maxHunger, m_life, m_lifespan;
};

