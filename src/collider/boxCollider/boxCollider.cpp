#include "precomp.h"
#include "boxCollider.h"

BoxCollider::BoxCollider(Surface* screen, int2 size) : Collider(screen)
{
	this->size = size;
	topLeft = new PointCollider(screen);
	topRight = new PointCollider(screen);
	bottomLeft = new PointCollider(screen);
	bottomRight = new PointCollider(screen);
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
	topLeft->Draw(visualSize, color);
	topRight->Draw(visualSize, color);
	bottomLeft->Draw(visualSize, color);
	bottomRight->Draw(visualSize, color);
	screen->Line(topLeft->GetPos().x, topLeft->GetPos().y, topRight->GetPos().x, topRight->GetPos().y, color);
	screen->Line(topRight->GetPos().x, topRight->GetPos().y, bottomRight->GetPos().x, bottomRight->GetPos().y, color);
	screen->Line(bottomRight->GetPos().x, bottomRight->GetPos().y, bottomLeft->GetPos().x, bottomLeft->GetPos().y, color);
	screen->Line(bottomLeft->GetPos().x, bottomLeft->GetPos().y, topLeft->GetPos().x, topLeft->GetPos().y, color);
}
