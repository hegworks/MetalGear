#include "precomp.h"
#include "boxAabb.h"

BoxAabb::BoxAabb(const float2 pos, const float2 size)
{
	m_size = size;
	UpdatePosition(pos);
}

void BoxAabb::UpdatePosition(const float2 pos)
{
	m_min = pos;
	m_max = pos + m_size;
}

#ifdef _DEBUG
void BoxAabb::Draw(Surface* pScreen, uint color) const
{
	const int2 minInt = {static_cast<int>(m_min.x),static_cast<int>(m_min.y)};
	const int2 maxInt = {static_cast<int>(m_max.x),static_cast<int>(m_max.y)};
	pScreen->Box(minInt.x, minInt.y, maxInt.x, maxInt.y, color);
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

bool BoxAabb::IsColliding(const float2 point) const
{
	return
		point.x >= m_min.x &&
		point.x <= m_max.x &&
		point.y >= m_min.y &&
		point.y <= m_max.y;
}
