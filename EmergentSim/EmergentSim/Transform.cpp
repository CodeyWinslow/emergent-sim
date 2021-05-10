#include "Transform.h"

Transform::Transform(int x, int y, Direction dir) : x(x), y(y), direction(dir)
{
}

void Transform::Forward(int count)
{
	switch (direction)
	{
	case Direction::UP:
		y += count;
		break;
	case Direction::DOWN:
		y -= count;
		break;
	case Direction::RIGHT:
		x += count;
		break;
	case Direction::LEFT:
		x -= count;
		break;
	}
}

void Transform::Turn(int numTimes)
{
	int dir = direction;
	dir += numTimes;
	direction = static_cast<Direction>(dir % 4);
}