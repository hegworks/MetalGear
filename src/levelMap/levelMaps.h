#pragma once
#include "levelMap.h"

constexpr int TOTAL_LEVEL_MAPS = 5;

class LevelMaps
{
public:
	int** GetLevelMapPointers(int id);
};
