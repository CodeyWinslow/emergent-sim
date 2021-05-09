#include "Sandbox.h"

Sandbox::Sandbox(int width, int height) : m_width(width), m_height(height)
{
	SetupSandbox();
}

void Sandbox::SetupSandbox()
{
	//X * Y 

	//
}

Sandbox::~Sandbox()
{
	m_width = 0;
	m_height = 0;
}
