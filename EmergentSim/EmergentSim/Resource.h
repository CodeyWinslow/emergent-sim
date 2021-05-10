#pragma once
#include "Entity.h"
class Resource : public Entity
{
public:
	Resource(Transform transform);
	inline virtual EntityType GetType() { return EntityType::RESOURCE; }
};