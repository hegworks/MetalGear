#pragma once
#include "src/human/enemy/enemy.h"
#include "src/human/player/player.h"

constexpr int MAX_ENEMIES = 2;

class EnemySpawner
{
public:
	EnemySpawner(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, Player* player, BulletManager* pBulletManager);
	bool Spawn();

	Enemy* enemies[MAX_ENEMIES];
	int enemyCount = 0;

private:
	Surface* screen = nullptr;
	LevelMaps* levelMaps = nullptr;
	SpriteStorage* spriteStorage = nullptr;
	Player* player = nullptr;
	BulletManager* bulletManager = nullptr;
};
