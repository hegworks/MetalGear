#pragma once
#include "src/tile/levelMap/levelMaps.h"

class Collider
{
public:
	Collider(Surface* pScreen, LevelMaps* pLevelMaps);
	virtual ~Collider() = default;
#ifdef _DEBUG
	virtual void Draw(float visualSize, int color = 0xff0000) = 0;
#endif

protected:
	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
};
