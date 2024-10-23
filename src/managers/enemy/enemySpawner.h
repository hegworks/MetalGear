#pragma once
#include "src/human/enemy/enemy.h"
#include "src/human/player/player.h"

class AudioManager;
constexpr int MAX_ENEMIES = 2;

class EnemySpawner
{
public:
	EnemySpawner(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);
	void Tick(float deltaTime);
	void Draw() const;
#ifdef _DEBUG
	void DrawColliders() const;
#endif
	bool Spawn();
	void PlayerPunchReported() const;
	void RoomChanged();

private:
	Surface* m_screen = nullptr;
	LevelMaps* m_levelMaps = nullptr;
	SpriteStorage* m_spriteStorage = nullptr;
	Player* m_player = nullptr;
	BulletManager* m_bulletManager = nullptr;
	AudioManager* m_audioManager = nullptr;

	Enemy* m_enemies[MAX_ENEMIES];
	int m_enemyCount = 0;
	bool m_hasAlertedAllInRoom = false;
};
