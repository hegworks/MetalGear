#pragma once
#include "src/collider/collider.h"

class PointCollider : public Collider
{
public:
	PointCollider(Surface* screen) : Collider(screen) {	}

	void UpdatePosition(int2 pos);
	void Draw(int size, int color = 0xff0000);
	int2 GetPos() const { return pos; }

private:
	int2 pos;
};
