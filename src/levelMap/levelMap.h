#pragma once
class LevelMap
{
public:
	static constexpr int ROWS = 24;
	static constexpr int COLS = 32;

	LevelMap(const int id, const int map[ROWS][COLS]);
	int map[ROWS][COLS];
	int id;
};
