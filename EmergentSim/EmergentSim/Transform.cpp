#include "Transform.h"

Transform::Transform(int x, int y, Direction dir) : m_x(x), m_y(y), m_dir(dir)
{
}

void Transform::Forward(int count)
{
	switch (m_dir)
	{
	case Direction::UP:
		m_y += count;
		break;
	case Direction::DOWN:
		m_y -= count;
		break;
	case Direction::RIGHT:
		m_x += count;
		break;
	case Direction::LEFT:
		m_x -= count;
		break;
	}
}
