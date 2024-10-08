#pragma once
#include "src/tile/levelMap/levelMaps.h"

class Collider
{
public:
	Collider(Surface* pScreen, LevelMaps* pLevelMaps);

	virtual void Draw(int size, int color = 0xff0000) = 0;

protected:
	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
};
