#pragma once
class Transform
{
public:
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Transform(int x, int y, Direction dir);
	void Forward(int count);

	int m_x = 0;
	int m_y = 0;
	Direction m_dir;
};