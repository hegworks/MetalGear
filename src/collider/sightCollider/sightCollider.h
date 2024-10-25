#pragma once
#include "src/collider/collider.h"
#include "src/human/direction.h"

class Player;
class PointCollider;

constexpr int SIGHT_COLL_SIZE = 30;

class SightCollider : public Collider
{
public:
	SightCollider(Surface* pScreen, LevelMaps* pLevelMaps, Player* pPlayer);
	virtual ~SightCollider();

	void UpdatePosition(float2 startPos, Direction dir);
#ifdef _DEBUG
	virtual void Draw(float visualSize, int color = 0xff0000);
#endif
	bool IsPlayerInSight() const;

private:
	PointCollider* m_pPoints[SIGHT_COLL_SIZE] = {};
	Player* m_pPlayer = nullptr;
	Direction m_dir{};

	bool IsOutOfScreen(float2 pos) const;
};
