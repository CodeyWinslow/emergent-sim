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
	void Forward(int numCells);
	void Turn(int numTimes);

	int x = 0;
	int y = 0;
	Direction direction;
};