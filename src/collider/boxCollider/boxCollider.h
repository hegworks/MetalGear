#pragma once
#include "src/collider/collider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/human//direction.h"

class BoxCollider : public Collider
{
public:
	BoxCollider(Surface* screen, LevelMaps* levelMaps, int2 size);

	void UpdatePosition(int2 pos);
	void Draw(int visualSize, int color = 0xff0000) override;
	int2 GetSize() const { return size; }
	bool IsSolid(Direction direction);

private:
	int2 pos;
	int2 size;

	PointCollider* topLeft;
	PointCollider* topRight;
	PointCollider* bottomLeft;
	PointCollider* bottomRight;
};
