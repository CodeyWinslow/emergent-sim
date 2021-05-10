#pragma once
#include "Entity.h"
class Wall : public Entity
{
public:
	Wall(Transform transform);
	inline virtual EntityType GetType() { return EntityType::WALL; }
};