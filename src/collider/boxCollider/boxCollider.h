#pragma once
#include "src/collider/collider.h"
#include "src/collider/pointCollider/pointCollider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Surface* screen, int2 size);

	void UpdatePosition(int2 pos);
	void Draw(int visualSize, int color = 0xff0000) override;
	int2 GetSize() const { return size; }

private:
	int2 pos;
	int2 size;

	PointCollider* topLeft;
	PointCollider* topRight;
	PointCollider* bottomLeft;
	PointCollider* bottomRight;
};
