#include "precomp.h"
#include "pointCollider.h"

void PointCollider::UpdatePosition(float2 pos)
{
	m_pos = pos;
}

bool PointCollider::IsSolid() const
{
	return m_pLevelMaps->IsSolid(m_pos);
}

#ifdef _DEBUG
void PointCollider::Draw(const float visualSize, const int color)
{
	const int2 startPosInt = {static_cast<int>(m_pos.x),static_cast<int>(m_pos.y)};
	const int2 endPosInt = {static_cast<int>(m_pos.x + visualSize),static_cast<int>(m_pos.y + visualSize)};
	m_pScreen->Bar(startPosInt.x, startPosInt.y, endPosInt.x, endPosInt.y, color);
}
#endif
