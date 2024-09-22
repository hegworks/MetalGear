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

void BoxCollider::UpdatePosition(int2 pos)
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
	screen->Line(topLeft->GetPos().x, topLeft->GetPos().y, topRight->GetPos().x, topRight->GetPos().y, color);
	screen->Line(topRight->GetPos().x, topRight->GetPos().y, bottomRight->GetPos().x, bottomRight->GetPos().y, color);
	screen->Line(bottomRight->GetPos().x, bottomRight->GetPos().y, bottomLeft->GetPos().x, bottomLeft->GetPos().y, color);
	screen->Line(bottomLeft->GetPos().x, bottomLeft->GetPos().y, topLeft->GetPos().x, topLeft->GetPos().y, color);
#endif
}

bool BoxCollider::IsSolid(Direction direction)
{
	switch(direction)
	{
		case Direction::Up:
			return levelMaps->IsSolid(topLeft->GetPos()) || levelMaps->IsSolid(topRight->GetPos());
		case Direction::Down:
			return levelMaps->IsSolid(bottomLeft->GetPos()) || levelMaps->IsSolid(bottomRight->GetPos());
		case Direction::Left:
			return levelMaps->IsSolid(topLeft->GetPos()) || levelMaps->IsSolid(bottomLeft->GetPos());
		case Direction::Right:
			return levelMaps->IsSolid(topRight->GetPos()) || levelMaps->IsSolid(bottomRight->GetPos());
	}
}
