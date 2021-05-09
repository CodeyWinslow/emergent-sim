#include "Sandbox.h"

Sandbox::Sandbox(int width, int height) : m_width(width), m_height(height)
{}

Sandbox::~Sandbox()
{
	m_width = 0;
	m_height = 0;
}

/*void Sandbox::VisitAll(void (*Visit)(Entity* entity))
{
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			Visit(m_sandbox[i][j]);
		}
	}
}*/
