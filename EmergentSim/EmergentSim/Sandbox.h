#pragma once
#include "Entity.h"
#include <vector>
#include <stdlib.h>
using std::vector;

//Temp variables to be put in game controller
float const MIN_WALL_PERCENT = 0;
float const MAX_WALL_PERCENT = .15f;
float const MIN_RESOURCE_PERCENT = .10f;
float const MAX_RESOURCE_PERCENT = .30f;

class Sandbox
{
public:
	Sandbox(int width, int height);
	~Sandbox();
	inline int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	inline Entity* GetEntity(int x, int y) { return m_sandbox[x][y]; }

	bool RandomlyPlaceEntity(Entity* ent);
	bool PlaceEntity(Entity* ent, int x, int y);
private:
	void SetupSandbox();

	int m_width = 0;
	int m_height = 0;
	int m_entityCount = 0;
	vector<vector<Entity*>> m_sandbox;
};