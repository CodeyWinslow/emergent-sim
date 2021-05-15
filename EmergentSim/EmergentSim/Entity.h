#pragma once
#include "Transform.h"
#include "IRenderable.h"

using namespace EmergentGraphics;

class Sprite;

enum EntityType 
{ 
	AGENT = 0, 
	RESOURCE = 1, 
	WALL = 2
};

class Entity : public IRenderable
{
public:
	Entity(Transform transform, SDL_Color color) : m_transform(transform), m_color(color) {};
	inline virtual const EntityType GetType() const = 0;
	inline virtual Transform GetTransform() { return m_transform; }
	inline virtual const Transform GetTransform() const { return m_transform; }

	inline virtual void Draw(Camera* camera) const { camera->Draw(m_transform, m_color); }

	Transform m_transform;
protected:
	SDL_Color m_color;
private:
	Sprite* m_sprite = nullptr;
};