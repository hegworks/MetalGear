#pragma once
#include "src/collider/collider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/human//direction.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Surface* pScreen, LevelMaps* pLevelMaps, int2 size);

	void UpdatePosition(float2 pos);
#ifdef _PHYSICS_DEBUG
	virtual void Draw(float visualSize, int color = 0xff0000);
#endif
	int2 GetSize() const { return m_size; }
	bool IsSolid(Direction direction) const;

private:
	float2 m_pos = {};
	int2 m_size = {};

	PointCollider* m_topLeft = nullptr;
	PointCollider* m_topRight = nullptr;
	PointCollider* m_bottomLeft = nullptr;
	PointCollider* m_bottomRight = nullptr;
};
