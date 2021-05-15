#pragma once
#include "Entity.h"
#include <vector>
#include <stdlib.h>
using std::vector;

//Temp variables to be put in game controller
float const MIN_WALL_PERCENT = 0.02;
float const MAX_WALL_PERCENT = 0.15f;
float const MIN_RESOURCE_PERCENT = 0.5f;
float const MAX_RESOURCE_PERCENT = 0.8f;

class Sandbox
{
public:
	Sandbox(int width, int height);
	~Sandbox();
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline const Entity* GetEntity(int x, int y) const { return m_sandbox[x][y]; }

	bool RandomlyPlaceEntity(Entity* ent);
	bool PlaceEntity(Entity* ent, int x, int y);
	bool MoveEntity(Entity* ent, Transform destination);
	bool RemoveEntity(const Entity* ent);
	const Entity* At(Transform transform) const;
	vector<Entity*> GetEntitiesInView(const Entity* ent, unsigned int distance) const;
private:
	void SetupSandbox();

	int m_width = 0;
	int m_height = 0;
	int m_entityCount = 0;
	vector<vector<Entity*>> m_sandbox;
};