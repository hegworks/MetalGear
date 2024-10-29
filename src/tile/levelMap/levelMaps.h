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
	int GetCurrentLevelId() const { return m_currentLevelId; }
	void SetCurrentLevelId(const int id) { m_currentLevelId = id; }
	TileType GetTileType(float2 pos) const;
	TileType GetTileType(int tileIndex) const;
	bool IsSolid(float2 pos) const;
	int2 GetTilePos(float2 pos) const;
	void DeleteCurrentColliders() const;

private:
	int m_tiles[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS];
	int m_colls[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS];
	int** m_ppMaps = nullptr;
	int** m_ppColliders = nullptr;
	int m_currentLevelId = 0;

	int GetCollValue(float2 pos) const;
};
