#pragma once
#include "src/tile/tileType.h"

constexpr int TOTAL_LEVEL_MAPS = 10;
constexpr int LEVELMAP_ROWS = 24;
constexpr int LEVELMAP_COLS = 32;

class LevelMaps
{
public:
	LevelMaps();
	int** GetLevelMapPointers();
	int** GetLevelColliderPointers();
	int GetCurrentLevelId() const { return currentLevelId; }
	void SetCurrentLevelId(const int id) { currentLevelId = id; }
	TileType GetTileType(int2 pos) const;
	bool IsSolid(int2 pos) const;

private:
	const int (*tiles)[LEVELMAP_ROWS][LEVELMAP_COLS];
	const int (*colls)[LEVELMAP_ROWS][LEVELMAP_COLS];
	int currentLevelId = 0;

	int GetCollValue(int2 pos) const;
};
