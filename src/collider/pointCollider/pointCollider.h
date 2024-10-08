#pragma once
#include "src/collider/collider.h"

class PointCollider : public Collider
{
public:
	PointCollider(Surface* pScreen, LevelMaps* pLevelMaps) : Collider(pScreen, pLevelMaps) {}

	void UpdatePosition(float2 pos);
#ifdef _PHYSICS_DEBUG
	virtual void Draw(float visualSize, int color = 0xff0000);
#endif
	float2 GetPos() const { return m_pos; }
	TileType GetTileType() const { return m_pLevelMaps->GetTileType(m_pos); }

private:
	float2 m_pos = {};
};
