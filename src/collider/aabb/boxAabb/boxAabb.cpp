#include "precomp.h"
#include "boxAabb.h"

BoxAabb::BoxAabb(const float2 pos, const float2 size)
{
	m_size = size;
	UpdatePosition(pos);
}

void BoxAabb::UpdatePosition(const float2 pos)
{
	m_pos = pos;
	m_min = m_pos;
	m_max = m_pos + m_size;
}

#ifdef _PHYSICS_DEBUG
void BoxAabb::Draw(Surface* pScreen, uint color) const
{
	const int2 pos = {static_cast<int>(m_pos.x),static_cast<int>(m_pos.y)};
	const int2 size = {static_cast<int>(m_size.x),static_cast<int>(m_size.y)};
	pScreen->Box(pos.x, pos.y, pos.x + size.x, pos.y + size.y, color);
}
#endif

bool BoxAabb::IsColliding(const BoxAabb* other) const
{
	return
		m_min.x <= other->GetMax().x &&
		m_max.x >= other->GetMin().x &&
		m_min.y <= other->GetMax().y &&
		m_max.y >= other->GetMin().y;
}
