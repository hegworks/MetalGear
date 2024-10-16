#include "precomp.h"
#include "circleAabb.h"

CircleAabb::CircleAabb(const float2 pos, const float radius)
{
	m_pos = pos;
	m_radius = radius;
}

void CircleAabb::UpdatePosition(const float2 pos)
{
	m_pos = pos;
}

#ifdef _DEBUG
void CircleAabb::Draw(Surface* pScreen, uint color) const
{
	int2 posInt = {static_cast<int>(m_pos.x), static_cast<int>(m_pos.y)};
	pScreen->Circle(posInt.x, posInt.y, static_cast<int>(m_radius), 0x00ff00);
}
#endif

bool CircleAabb::IsColliding(const CircleAabb* other) const
{
	return Distance(m_pos, other->GetPos()) < m_radius + other->GetRadius();
}

bool CircleAabb::IsColliding(const float2 point) const
{
	return Distance(m_pos, point) < m_radius;
}

float CircleAabb::Distance(const float2 a, const float2 b) const
{
	return sqrt
	(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y)
	);
}
