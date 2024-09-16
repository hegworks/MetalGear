#pragma once

class LevelMaps
{
public:
	LevelMaps();
	int** GetLevelMapPointers(int id);

private:
	int levelMaps[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS];
};
