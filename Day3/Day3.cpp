#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

enum direction { right, down, left, up };

int partOne(int number)
{
	int max_x = (int)floor(sqrt(number)) + 1;
	int max_y = (int)floor(sqrt(number)) + 1;

	int x = ((max_x) / 2);
	int y = ((max_y) / 2);

	int stepsCount = 0;
	int stepsInDirection = 1;
	int stepsInDirectionCount = 0;

	direction dir = direction::right;

	for (int i = 2; i <= number; i++)
	{
		switch (dir)
		{
		case direction::right:
			x += 1;
			break;
		case direction::down:
			y += 1;
			break;
		case direction::left:
			x -= 1;
			break;
		case direction::up:
			y -= 1;
			break;
		}

		stepsCount += 1;
		if (stepsCount == stepsInDirection)
		{
			stepsCount = 0;
			stepsInDirectionCount += 1;

			if (stepsInDirectionCount == 2)
			{
				stepsInDirection += 1;
				stepsInDirectionCount = 0;
			}

			switch (dir)
			{
			case direction::right:
				dir = direction::up;
				break;
			case direction::down:
				dir = direction::right;
				break;
			case direction::left:
				dir = direction::down;
				break;
			case direction::up:
				dir = direction::left;
				break;
			}
		}
	}

	return abs(x - ((max_x) / 2)) + abs(y - ((max_y) / 2));
}

int partTwo(int number)
{
	int max_x = (int)floor(sqrt(number)) + 1;
	int max_y = (int)floor(sqrt(number)) + 1;

	vector<vector<int>> matrix;

	matrix.resize(max_y + 1);

	for (int i = 0; i < max_y + 1; i++)
		matrix[i].resize(max_x + 1);

	for (int i = 0; i < max_x + 1; i++)
		for (int j = 0; j < max_y + 1; j++)
			matrix[i][j] = 0;

	int x = ((max_x) / 2);
	int y = ((max_y) / 2);

	// Initialize the central element
	matrix[x][y] = 1;

	int stepsCount = 0;
	int stepsInDirection = 1;
	int stepsInDirectionCount = 0;

	direction dir = direction::right;

	for (int i = 2; i < number; i++)
	{
		switch (dir)
		{
		case direction::right:
			x += 1;
			break;
		case direction::down:
			y += 1;
			break;
		case direction::left:
			x -= 1;
			break;
		case direction::up:
			y -= 1;
			break;
		}
		matrix[y][x] = matrix[y][x - 1] +
			matrix[y][x + 1] +
			matrix[y + 1][x] +
			matrix[y - 1][x] +
			matrix[y - 1][x - 1] +
			matrix[y - 1][x + 1] +
			matrix[y + 1][x - 1] +
			matrix[y + 1][x + 1];

		if (matrix[y][x] > number)
		{
			return matrix[y][x];
		}

		stepsCount += 1;
		if (stepsCount == stepsInDirection)
		{
			stepsCount = 0;
			stepsInDirectionCount += 1;

			if (stepsInDirectionCount == 2)
			{
				stepsInDirection += 1;
				stepsInDirectionCount = 0;
			}

			switch (dir)
			{
			case direction::right:
				dir = direction::up;
				break;
			case direction::down:
				dir = direction::right;
				break;
			case direction::left:
				dir = direction::down;
				break;
			case direction::up:
				dir = direction::left;
				break;
			}
		}
	}

	return abs(x - ((max_x) / 2)) + abs(y - ((max_y) / 2));
}

int _tmain(int argc, _TCHAR* argv[])
{
	const int number = 347991;

	cout << "Distance from part 1 is : " << partOne(number) << endl;

	cout << "Result from part 2 is : " << partTwo(number) << endl;

	cin.ignore();

	return 0;
}