#pragma once
#include "src/tile/levelMap/levelMaps.h"

class Collider
{
public:
	Collider(Surface* pScreen, LevelMaps* pLevelMaps);
	~Collider() {}

	virtual void Draw(const int size) {}
	virtual void Draw(int size, int color = 0xff0000) {}

protected:
	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
};
