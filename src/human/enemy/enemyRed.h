#pragma once
#include "enemy.h"

class EnemyRed : public Enemy
{
public:
	EnemyRed(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);

	virtual void Tick(float deltaTime);
	virtual void Lookaround(float deltaTime);
	virtual void Relieve();
	virtual void ComeBack(int comebackOrder);

private:
	const float LOOKAROUND_TIME = 1000.0f;
	const float SPEED_CHASE = 0.35f;
	const float COMEBACK_ORDER_1_SPAWN_TIME = 1500.0f;
	float m_comeBackOrder1SpawnTimer = 0;
	// comeback
	int m_comeBackOrder = 0;
	const float ORDER_0_ESD_X = 288;
	bool m_isOrder1WaitingToSpawn = false;

	void CheckLookAroundCollider();
	void CheckComeBackOrder1Spawn(float deltaTime);
};
