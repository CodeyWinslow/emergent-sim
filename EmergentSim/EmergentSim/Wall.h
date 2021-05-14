#pragma once

#include "Entity.h"
class Wall : public Entity
{
public:
	Wall(Transform transform, SDL_Color color = { 13, 137, 214, 255 });
	inline virtual EntityType GetType() { return EntityType::WALL; }
};