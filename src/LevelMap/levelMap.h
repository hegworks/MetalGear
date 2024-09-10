#pragma once

class LevelMap
{
public:
	LevelMap(int** matrix, int rowCount, int columnCount);

	int** matrix;
	int rowCount;
	int columnCount;
};
