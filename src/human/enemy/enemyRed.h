#pragma once
#include "enemy.h"

class EnemyRed : public Enemy
{
public:
	EnemyRed(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);

	virtual void Tick(float deltaTime);
	virtual void Lookaround(float deltaTime);

private:
	const float LOOKAROUND_TIME = 1000.0f;
};
