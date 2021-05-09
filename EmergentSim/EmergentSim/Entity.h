#pragma once
#include "Transform.h"
class Sprite;

enum Entity_Type 
{ 
	AGENT = 0, 
	RESOURCE = 1, 
	WALL = 2
};

class Entity 
{
public:
	Entity(Transform transform) : m_transform(transform) {};
	inline virtual Entity_Type GetType() = 0;
	virtual Transform GetTransform() { return m_transform; }
private:

	Sprite* m_sprite = nullptr;
	Transform m_transform;
};