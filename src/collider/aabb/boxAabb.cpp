#include "precomp.h"
#include "boxAabb.h"

BoxAabb::BoxAabb(float2 pos, float2 size)
{
	m_size = size;
	UpdatePosition(pos);
}

void BoxAabb::UpdatePosition(float2 pos)
{
	m_pos = pos;
	m_min = m_pos;
	m_max = m_pos + m_size;
}

void BoxAabb::Draw(Surface* pScreen, uint color)
{
#ifdef _PHYSICS_DEBUG
	pScreen->Box(m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, color);
#endif
}

bool BoxAabb::IsColliding(const BoxAabb* other)
{
	return
		m_min.x <= other->GetMax().x &&
		m_max.x >= other->GetMin().x &&
		m_min.y <= other->GetMax().y &&
		m_max.y >= other->GetMin().y;
}
