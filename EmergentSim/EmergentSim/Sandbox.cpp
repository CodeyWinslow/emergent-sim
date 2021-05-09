#include "Sandbox.h"

Sandbox::Sandbox(int width, int height) : m_width(width), m_height(height)
{}

Sandbox::~Sandbox()
{
	m_width = 0;
	m_height = 0;
}
