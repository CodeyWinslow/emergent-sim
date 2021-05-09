#pragma once
#include "Entity.h"
class Wall : Entity
{
public:
	Wall(Transform transform);
	inline virtual Entity_Type GetType() { return Entity_Type::WALL; }

	Transform m_transform;
};