#pragma once
#include "Transform.h"
#include "IRenderable.h"
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
	inline virtual EntityType GetType() = 0;
	inline virtual Transform GetTransform() { return m_transform; }

	inline virtual void Draw(Camera* camera) { camera->Draw(m_transform, m_color); }

	Transform m_transform;
protected:
	SDL_Color m_color;
private:
	Sprite* m_sprite = nullptr;
};