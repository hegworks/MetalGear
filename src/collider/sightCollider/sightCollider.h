﻿#pragma once
#include "src/collider/collider.h"
#include "src/human/direction.h"

class Player;
class PointCollider;

constexpr int SIGHT_COLL_SIZE = 30;

class SightCollider : public Collider
{
public:
	SightCollider(Surface* pScreen, LevelMaps* pLevelMaps, Player* pPlayer);

	void UpdatePosition(int2 startPos, Direction dir);
	virtual void Draw(int visualSize, int color = 0xff0000) const;
	bool IsPlayerInSight();

private:
	PointCollider* m_pPoints[SIGHT_COLL_SIZE];
	Player* m_pPlayer = nullptr;
	Direction m_dir;

	bool IsOutOfScreen(int2 pos) const;
};