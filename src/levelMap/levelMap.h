#pragma once

class LevelMap
{
public:
	LevelMap(const int id, const int map[LEVELMAP_ROWS][LEVELMAP_COLS]);
	int map[LEVELMAP_ROWS][LEVELMAP_COLS];
	int id;
};
