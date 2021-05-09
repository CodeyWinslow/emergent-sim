#pragma once
class Transform
{
public:
	enum Direction
	{
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

	Transform(int x, int y, Direction dir);
	void Forward(int count);

	int m_x = 0;
	int m_y = 0;
	Direction m_dir;
};