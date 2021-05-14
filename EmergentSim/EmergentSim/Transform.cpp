#include "Transform.h"
#include <cmath>

Transform::Transform(int x, int y, Direction dir) : x(x), y(y), direction(dir)
{
}

void Transform::Forward(int count)
{
	switch (direction)
	{
	case Direction::UP:
		y -= count;
		break;
	case Direction::DOWN:
		y += count;
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
	if (dir < 0) dir += 4;
	direction = static_cast<Direction>(dir % 4);
}

float Transform::Distance(Transform t)
{
	double _x = x > t.x ? x - t.x : t.x - x;
	double _y = y > t.y ? y - t.y : t.y - y;
	_x *= _x;
	_y *= _y;
	return (float)sqrt(_x + _y);
}