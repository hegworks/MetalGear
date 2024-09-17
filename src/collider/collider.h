#pragma once
#include "src/tile/levelMap/levelMaps.h"

class Collider
{
public:
	Collider(Surface* screen, LevelMaps* levelMaps);
	~Collider() {}

	virtual void Draw(const int size) {}
	virtual void Draw(int size, int color = 0xff0000) {}

protected:
	Surface* screen;
	LevelMaps* levelMaps;
};
