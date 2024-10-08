#include "precomp.h"
#include "pointCollider.h"

void PointCollider::UpdatePosition(float2 pos)
{
	this->m_pos = pos;
}

#ifdef _PHYSICS_DEBUG
void PointCollider::Draw(const float visualSize, const int color)
{
	const int2 startPosInt = {static_cast<int>(m_pos.x),static_cast<int>(m_pos.y)};
	const int2 endPosInt = {static_cast<int>(m_pos.x + visualSize),static_cast<int>(m_pos.y + visualSize)};
	m_pScreen->Bar(startPosInt.x, startPosInt.y, endPosInt.x, endPosInt.y, color);
}
#endif
