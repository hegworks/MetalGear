#pragma once

constexpr int LEVELMAP_ROWS = 24;
constexpr int LEVELMAP_COLS = 32;

class LevelMap
{
public:
	LevelMap(const int id, const int map[LEVELMAP_ROWS][LEVELMAP_COLS]);
	int map[LEVELMAP_ROWS][LEVELMAP_COLS];
	int id;
};
