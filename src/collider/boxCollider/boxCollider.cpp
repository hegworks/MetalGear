#include "precomp.h"
#include "boxCollider.h"

BoxCollider::BoxCollider(Surface* screen, LevelMaps* levelMaps, int2 size) : Collider(screen, levelMaps)
{
	this->size = size;
	topLeft = new PointCollider(screen, levelMaps);
	topRight = new PointCollider(screen, levelMaps);
	bottomLeft = new PointCollider(screen, levelMaps);
	bottomRight = new PointCollider(screen, levelMaps);
}

void BoxCollider::UpdatePosition(float2 pos)
{
	this->pos = pos;
	topLeft->UpdatePosition(pos);
	topRight->UpdatePosition({pos.x + size.x, pos.y});
	bottomLeft->UpdatePosition({pos.x, pos.y + size.y});
	bottomRight->UpdatePosition({pos.x + size.x, pos.y + size.y});
}

void BoxCollider::Draw(int visualSize, int color)
{
#ifdef _PHYSICS_DEBUG
	topLeft->Draw(visualSize, color);
	topRight->Draw(visualSize, color);
	bottomLeft->Draw(visualSize, color);
	bottomRight->Draw(visualSize, color);
	m_pScreen->Line(topLeft->GetPos().x, topLeft->GetPos().y, topRight->GetPos().x, topRight->GetPos().y, color);
	m_pScreen->Line(topRight->GetPos().x, topRight->GetPos().y, bottomRight->GetPos().x, bottomRight->GetPos().y, color);
	m_pScreen->Line(bottomRight->GetPos().x, bottomRight->GetPos().y, bottomLeft->GetPos().x, bottomLeft->GetPos().y, color);
	m_pScreen->Line(bottomLeft->GetPos().x, bottomLeft->GetPos().y, topLeft->GetPos().x, topLeft->GetPos().y, color);
#endif
}

bool BoxCollider::IsSolid(Direction direction)
{
	switch(direction)
	{
		case Direction::Up:
			return m_pLevelMaps->IsSolid(topLeft->GetPos()) || m_pLevelMaps->IsSolid(topRight->GetPos());
		case Direction::Down:
			return m_pLevelMaps->IsSolid(bottomLeft->GetPos()) || m_pLevelMaps->IsSolid(bottomRight->GetPos());
		case Direction::Left:
			return m_pLevelMaps->IsSolid(topLeft->GetPos()) || m_pLevelMaps->IsSolid(bottomLeft->GetPos());
		case Direction::Right:
			return m_pLevelMaps->IsSolid(topRight->GetPos()) || m_pLevelMaps->IsSolid(bottomRight->GetPos());
	}
}
