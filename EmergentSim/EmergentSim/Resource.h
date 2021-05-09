#pragma once
#include "Entity.h"
class Resource : Entity
{
public:
	Resource(Transform transform);
	inline virtual Entity_Type GetType() { return Entity_Type::RESOURCE; }

	Transform m_transform;
};