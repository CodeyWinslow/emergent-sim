#pragma once
#include "Entity.h"
#include <vector>

class Sandbox
{
public:
	Sandbox(int width, int height);
	~Sandbox();
	inline int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
private:
	int m_width = 0;
	int m_height = 0;
	std::vector<Entity*> m_sandbox;
};