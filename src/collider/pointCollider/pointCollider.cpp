#include "precomp.h"
#include "pointCollider.h"

void PointCollider::UpdatePosition(int2 pos)
{
	this->pos = pos;
}

void PointCollider::Draw(const int size, int color)
{
	screen->Bar(pos.x - size / 2, pos.y - size / 2, pos.x + size / 2, pos.y + size / 2, color);
}
