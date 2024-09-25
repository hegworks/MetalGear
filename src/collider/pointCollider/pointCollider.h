#pragma once
#include "src/collider/collider.h"

class PointCollider : public Collider
{
public:
	PointCollider(Surface* pScreen, LevelMaps* pLevelMaps) : Collider(pScreen, pLevelMaps) {}

	void UpdatePosition(int2 pos);
	virtual void Draw(int size, int color = 0xff0000);
	int2 GetPos() const { return m_pos; }
	TileType GetTileType() const { return m_pLevelMaps->GetTileType(m_pos); }

private:
	int2 m_pos;
};
