#pragma once
#include "Entity.h"
class Resource : public Entity
{
public:
	Resource(Transform transform, SDL_Color color = { 13, 214, 78, 255 });
	inline virtual const EntityType GetType() const { return EntityType::RESOURCE; }
};