#include "precomp.h"
#include "pointCollider.h"

void PointCollider::UpdatePosition(int2 pos)
{
	this->m_pos = pos;
}

void PointCollider::Draw(const int size, int color)
{
#ifdef _PHYSICS_DEBUG
	m_pScreen->Bar(m_pos.x - size / 2, m_pos.y - size / 2, m_pos.x + size / 2, m_pos.y + size / 2, color);
#endif
}
