#include "precomp.h"
#include "boxCollider.h"

BoxCollider::BoxCollider(Surface* screen, LevelMaps* levelMaps, int2 size) : Collider(screen, levelMaps)
{
	m_size = size;
	m_topLeft = new PointCollider(screen, levelMaps);
	m_topRight = new PointCollider(screen, levelMaps);
	m_bottomLeft = new PointCollider(screen, levelMaps);
	m_bottomRight = new PointCollider(screen, levelMaps);
}

void BoxCollider::UpdatePosition(float2 pos)
{
	m_pos = pos;
	m_topLeft->UpdatePosition(pos);
	m_topRight->UpdatePosition({pos.x + m_size.x, pos.y});
	m_bottomLeft->UpdatePosition({pos.x, pos.y + m_size.y});
	m_bottomRight->UpdatePosition({pos.x + m_size.x, pos.y + m_size.y});
}

void BoxCollider::Draw(const float visualSize, const int color)
{
#ifdef _PHYSICS_DEBUG
	m_topLeft->Draw(visualSize, color);
	m_topRight->Draw(visualSize, color);
	m_bottomLeft->Draw(visualSize, color);
	m_bottomRight->Draw(visualSize, color);
	m_pScreen->Line(m_topLeft->GetPos().x, m_topLeft->GetPos().y, m_topRight->GetPos().x, m_topRight->GetPos().y, color);
	m_pScreen->Line(m_topRight->GetPos().x, m_topRight->GetPos().y, m_bottomRight->GetPos().x, m_bottomRight->GetPos().y, color);
	m_pScreen->Line(m_bottomRight->GetPos().x, m_bottomRight->GetPos().y, m_bottomLeft->GetPos().x, m_bottomLeft->GetPos().y, color);
	m_pScreen->Line(m_bottomLeft->GetPos().x, m_bottomLeft->GetPos().y, m_topLeft->GetPos().x, m_topLeft->GetPos().y, color);
#endif
}

bool BoxCollider::IsSolid(Direction direction)
{
	switch(direction)
	{
		case Direction::Up:
			return m_pLevelMaps->IsSolid(m_topLeft->GetPos()) || m_pLevelMaps->IsSolid(m_topRight->GetPos());
		case Direction::Down:
			return m_pLevelMaps->IsSolid(m_bottomLeft->GetPos()) || m_pLevelMaps->IsSolid(m_bottomRight->GetPos());
		case Direction::Left:
			return m_pLevelMaps->IsSolid(m_topLeft->GetPos()) || m_pLevelMaps->IsSolid(m_bottomLeft->GetPos());
		case Direction::Right:
			return m_pLevelMaps->IsSolid(m_topRight->GetPos()) || m_pLevelMaps->IsSolid(m_bottomRight->GetPos());
	}
	throw new exception("invalid direction");
}
