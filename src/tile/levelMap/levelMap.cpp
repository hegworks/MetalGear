#include "precomp.h"
#include "levelMap.h"

LevelMap::LevelMap(const int id, const int map[LEVELMAP_ROWS][LEVELMAP_COLS])
{
	this->id = id;
	for(int i = 0; i < LEVELMAP_ROWS; ++i)
	{
		for(int j = 0; j < LEVELMAP_COLS; ++j)
		{
			this->map[i][j] = map[i][j];
		}
	}
}
