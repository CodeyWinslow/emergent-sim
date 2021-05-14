#pragma once

class Transform
{
public:
	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Transform(int x, int y, Direction dir);
	void Forward(int numCells);
	void Turn(int numTimes);
	float Distance(Transform t);

	int x = 0;
	int y = 0;
	Direction direction;
};