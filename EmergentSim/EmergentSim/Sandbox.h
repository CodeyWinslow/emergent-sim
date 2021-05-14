#pragma once

#include "Entity.h"
#include <vector>
#include <stdlib.h>
using std::vector;

//Temp variables to be put in game controller
float const MIN_WALL_PERCENT = 0.02f;
float const MAX_WALL_PERCENT = 0.15f;
float const MIN_RESOURCE_PERCENT = 0.5f;
float const MAX_RESOURCE_PERCENT = 0.8f;

class Sandbox
{
public:
	Sandbox(int width, int height);
	~Sandbox();
	inline int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	inline EntityPtr GetEntity(int x, int y) { return m_sandbox[x][y]; }

	bool RandomlyPlaceEntity(EntityPtr ent);
	bool PlaceEntity(EntityPtr ent, int x, int y);
	bool MoveEntity(EntityPtr ent, Transform destination);
	bool RemoveEntity(EntityPtr ent);
	EntityPtr At(Transform transform);
	vector<EntityPtr> GetEntitiesInView(EntityPtr ent, unsigned int distance);
private:
	void SetupSandbox();

	int m_width = 0;
	int m_height = 0;
	int m_entityCount = 0;
	vector<vector<EntityPtr>> m_sandbox;
};