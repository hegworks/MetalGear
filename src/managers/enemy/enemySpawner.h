#pragma once
#include "src/actors/human/enemy/enemy.h"

constexpr int MAX_ENEMIES = 2;

class EnemySpawner
{
public:
	EnemySpawner(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
	bool Spawn();

	Enemy* enemies[MAX_ENEMIES];
	int enemyCount = 0;

private:
	Surface* screen = nullptr;
	LevelMaps* levelMaps = nullptr;
	SpriteStorage* spriteStorage = nullptr;
};
