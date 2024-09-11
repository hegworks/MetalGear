#pragma once
#include "levelMap.h"

class LevelMaps
{
public:
	static constexpr int TOTAL_LEVEL_MAPS = 5;
	int** GetLevelMapPointers(int id);
};
