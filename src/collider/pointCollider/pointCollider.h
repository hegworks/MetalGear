#pragma once
#include "src/collider/collider.h"

class PointCollider : public Collider
{
public:
	PointCollider(Surface* screen, LevelMaps* levelMaps) : Collider(screen, levelMaps) {}

	void UpdatePosition(int2 pos);
	void Draw(int size, int color = 0xff0000) override;
	int2 GetPos() const { return pos; }
	TileType GetTileType() const { return levelMaps->GetTileType(pos); }

private:
	int2 pos;
};
