#pragma once
#include "Transform.h"
class Sprite;

enum EntityType 
{ 
	AGENT = 0, 
	RESOURCE = 1, 
	WALL = 2
};

class Entity 
{
public:
	Entity(Transform transform) : m_transform(transform) {};
	inline virtual EntityType GetType() = 0;
	virtual Transform GetTransform() { return m_transform; }

	Transform m_transform;
private:
	Sprite* m_sprite = nullptr;
};