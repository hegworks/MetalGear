#pragma once
#include "levelMap.h"

constexpr int TOTAL_LEVEL_MAPS = 1;

class LevelMaps
{
public:
	LevelMaps();
	int** GetLevelMapPointers(int id);
	int** GetLevelColliderPointers(int id);

private:
	int levelMaps[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS];
	int levelColliders[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS];
};
