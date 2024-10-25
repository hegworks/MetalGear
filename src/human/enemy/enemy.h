#pragma once
#include "enemyState.h"
#include "enemyType.h"
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"

enum class EnemyType;
class BulletManager;
class BoxAabb;
class Player;
class SightCollider;
class PointCollider;
class Rng;

constexpr int ENEMY_ANIMATION_COUNT = 4;

class Enemy : public Human
{
public:
	Enemy(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager);
	virtual void Tick(float deltaTime);
#ifdef _DEBUG
	virtual void DrawColliders();
#endif
	virtual void Draw() const;
	void PlayerPunchReported();
	void OneEnemyAlarmedReport();
	bool ReportIsAlerted() const { return m_state == EnemyState::Alarm; }
	EnemyState GetEnemyState() const { return m_state; }
	virtual void Relieve() {}
	virtual void ComeBack(int comebackOrder) {}

protected:
	EnemyState m_state = EnemyState::Patrol;

	// references
	Rng* m_pRng = nullptr;

	// LookAround
	float m_lookaroundTimer = 0.0f;
	Direction m_movementDirectionAfterLookAround = Direction::Up;
	Direction m_movementDirectionBeforeLookAround = Direction::Up;

	// colliders
	PointCollider* m_patrolCollider = nullptr;

	// functions
	void UpdatePatrolCollider() const;
	void CheckSightCollider();
	void UpdateSightCollider() const;
	void UpdateSightCollider(Direction direction) const;
	virtual void CheckPatrolCollider();
	virtual void Lookaround(float deltaTime);
	void MoveInDirection(float deltaTime);
	void UpdateAnimationState();
	void Animate(float deltaTime);
	void ChasePlayer(float deltaTime);
	void Shoot(float deltaTime);
	int2 GetSightColliderPos() const;
	void UpdateBoxAabb() const;
	void UpdateTimers(float deltaTime);
	void PunchShake(float deltaTime);
	void SwitchState(EnemyState newState);
	virtual void SetSpeedToChaseSpeed();
	virtual void SetSpeedToPatrolSpeed();
#ifdef _DEBUG
	void Debug_PrintValues() const;
#endif
	float2 GetCenterPos() const;
	virtual void UpdateBroadPhaseCircleAabb() const;

private:
	// colliders
	const float patrolColliderXOffset = 0;
	const float patrolColliderYOffset = TILESET_TILEWIDTH / 2.0f;

	SightCollider* m_pSightCollider = nullptr;

	// animation
	const float ANIMATION_UPDATE_TIME = 200.0f;
	float animationUpdateTimer = 0.0f;
	CustomAnimation animations[ENEMY_ANIMATION_COUNT] =
	{
		{AnimationType::Up, 6, 8 },
		{AnimationType::Down, 0, 2 },
		{AnimationType::Left, 3, 5 },
		{AnimationType::Right, 9, 11 },
	};

	// references
	Player* m_pPlayer = nullptr;
	BulletManager* m_pBulletManager = nullptr;

	// look around
	const int LOOKAROUND_CHANCE = 50;
	bool m_isOneStageOfLookOutPlaying = false;
	int m_lookAroundChecksDone = 0;
	const float LOOKAROUND_TIME = 500.0f;

	// speed
	const float SPEED_PATROL = 0.1f;
	const float SPEED_CHASE = 0.2f;

	// chase
	Direction m_chaseDirectionBeforeCollision = Direction::Up;
	bool m_chaseHasEverCollided = false;
	int m_chaseNoMovementCount = 0;

	// punch
	BoxAabb* m_boxAabb = nullptr;
	int m_debug_gotPunchedFrameCounter = 0;
	const float PUNCH_SHAKE_MAX_DISTANCE = 32;
	float m_yBeforePunchShake = 0;
	const float PUNCH_SHAKE_SPEED = 0.3f;
	bool m_isPunchShakeDirectionUp = true;
	bool m_isPunchShakePlaying = false;
	const float PUNCH_SHAKE_SHOOT_STOP_DURATION = 700;
	float m_punchShakeShootStopRemaining = 0;

	// HP
	const int MAX_HP = 3;
	int m_hp = MAX_HP;

	// shoot
	const float SHOOT_TIME = 1500.0f; // the time between each shoot
	float m_shootTimer = 0;
	const float SHOOT_STOP_DURATION = 300.0f; // the time to stop moving after shoot
	float m_shootStopRemaining = 0;
};
