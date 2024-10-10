#pragma once
#include "enemyState.h"
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"

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
	Enemy(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer, BulletManager* pBulletManager);
	virtual void Tick(float deltaTime);
#ifdef _PHYSICS_DEBUG
	virtual void DrawColliders();
#endif
	virtual void Draw() const;
	void PlayerPunchReported();
	void ForceAlarmState();
	bool ReportIsAlerted() const { return m_state == EnemyState::Alarm; }

private:
	// colliders
	PointCollider* patrolCollider = nullptr;
	const float patrolColliderXOffset = 0;
	const float patrolColliderYOffset = TILESET_TILEWIDTH / 2.0f;

	SightCollider* m_pSightCollider = nullptr;

	// animation
	const float ANIMATION_UPDATE_TIME = 200.0f;
	float animationUpdateTimer = 0.0f;
	CustomAnimation animations[ENEMY_ANIMATION_COUNT] =
	{
		{AnimationState::Up, 6, 8 },
		{AnimationState::Down, 0, 2 },
		{AnimationState::Left, 3, 5 },
		{AnimationState::Right, 9, 11 },
	};

	// references
	Rng* m_pRng = nullptr;
	Player* m_pPlayer = nullptr;
	BulletManager* m_pBulletManager = nullptr;

	EnemyState m_state = EnemyState::Patrol;

	// look around
	Direction m_movementDirectionAfterLookAround = Direction::Up;
	Direction m_movementDirectionBeforeLookAround = Direction::Up;
	static constexpr  int LOOKAROUND_CHANCE = 50;

	// speed
	const float SPEED = 0.1f;
	const float SPEED_CHASE = 0.15f;

	// chase
	Direction m_chaseDirectionBeforeCollision = Direction::Up;
	bool m_chaseHasEverCollided = false;
	int m_chaseNoMovementCount = 0;

	// punch
	BoxAabb* m_boxAabb = nullptr;
	int m_debug_gotPunchedFrameCounter = 0;

	// HP
	const int MAX_HP = 3;
	int m_hp = MAX_HP;

	// LookAround
	float m_lookaroundTimer = 0.0f;
	const float LOOKAROUND_TIME = 500.0f;
	Direction m_lookAroundDirection = Direction::Up;
	bool m_isOneStageOfLookOutPlaying = false;
	int m_lookAroundChecksDone = 0;

	// shoot
	float m_shootTimer = 0;
	const float SHOOT_TIME = 800.0f;

	// functions
	void UpdatePatrolCollider() const;
	void CheckSightCollider();
	void UpdateSightCollider() const;
	void UpdateSightCollider(Direction direction) const;
	void CheckPatrolCollider();
	void Lookaround(float deltaTime);
	void MoveInDirection(float deltaTime);
	void UpdateAnimationState();
	void Animate(float deltaTime);
	void ChasePlayer(float deltaTime);
	void Shoot(float deltaTime);
	int2 GetSightColliderPos() const;
	void UpdateBoxAabb() const;
#ifdef _PHYSICS_DEBUG
	void Debug_PrintValues() const;
#endif
	float2 GetCenterPos() const;
	virtual void UpdateBroadPhaseCircleAabb() const;
};
