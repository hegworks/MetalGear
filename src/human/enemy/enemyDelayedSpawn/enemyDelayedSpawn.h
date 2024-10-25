#pragma once
#include "src/human/enemy/enemy.h"

class EnemyDelayedSpawn : public Enemy
{
public:
	EnemyDelayedSpawn(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);

	virtual void Tick(float deltaTime);
	virtual void CheckPatrolCollider();
#ifdef _DEBUG
	virtual void DrawColliders();
#endif

private:
	const float HIDDEN_TIME = 3000.0f;
	float m_hiddenTimer = 0;

	void CheckHiddenTimer(float deltaTime);
};
