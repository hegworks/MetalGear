#pragma once
#include "src/human/enemy/enemy.h"
#include "src/human/player/player.h"

constexpr int MAX_ENEMIES = 2;

class EnemySpawner
{
public:
	EnemySpawner(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, Player* pPlayer, BulletManager* pBulletManager);
	bool Spawn();
	Enemy* enemies[MAX_ENEMIES];
	int GetEnemyCount() const { return m_enemyCount; }

private:
	Surface* m_screen = nullptr;
	LevelMaps* m_levelMaps = nullptr;
	SpriteStorage* m_spriteStorage = nullptr;
	Player* m_player = nullptr;
	BulletManager* m_bulletManager = nullptr;
	int m_enemyCount = 0;
};
