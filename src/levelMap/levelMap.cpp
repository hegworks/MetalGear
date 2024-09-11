#include "precomp.h"
#include "levelMap.h"

LevelMap::LevelMap(const int id, const int map[ROWS][COLS])
{
	this->id = id;
	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLS; ++j)
		{
			this->map[i][j] = map[i][j];
		}
	}
}
