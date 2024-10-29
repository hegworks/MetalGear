#pragma once
#include "src/animation/AnimationState.h"
#include "src/human/enemy/enemy.h"
#include "src/human/player/player.h"

class AudioManager;
constexpr int MAX_ENEMIES = 2;

class EnemySpawner
{
public:
	EnemySpawner(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);
	~EnemySpawner();
	void Tick(float deltaTime);
	void Draw() const;
#ifdef _DEBUG
	void DrawColliders() const;
#endif
	bool Spawn();
	void PlayerPunchReported() const;
	void RoomChanged();
	void CheckRelieveAndComeBackRoom8(float deltaTime);

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
	bool m_hasReportedAllEnemiesDeadOnce = false;

	// room 8 variables
	bool m_isInRoom8 = false;
	const float RELIEVE_TIME = 4000.0f;
	float m_relieveTimer = 0;
	const float COMEBACK_TIME = 4000.0f;
	float m_comeBackTimer = 0;
	const float WALK_TIME = 8000.0f;
	float m_walkTimer = 0;
	AnimationState m_walkAnimationState = AnimationState::NotStarted;
	enum class Room8State
	{
		OnGuard = 0,
		Relieve = 1,
	};
	Room8State m_room8State = Room8State::OnGuard;
	// relieve sprite & animation variables
	Sprite* m_relieveSprite = nullptr;
	const float2 RELIEVE_SPRITE_POS = {650,130};
	float m_relieveScale = 0;
	const float RELIEVE_ANIMATION_TIME = 400.0f;
	float m_relieveAnimationTimer = 0;
	AnimationState m_relieveAnimationState = AnimationState::NotStarted;
	const float RELIEVE_HIDE_TIME = 800;
	float m_relieveHideTimer = 0;

	void PlayRelieveSpriteAnimation(float deltaTime);
	void StartRelieveSpriteAnimation();
	void CheckRelieveHideTimer(float deltaTime);
	void PlayWalkAnimation(float deltaTime);
	void StartWalkAnimation();
	void ResetRoom8State();
};
