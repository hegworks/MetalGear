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
	virtual void DrawColliders();
	virtual void Draw() const;
	void PlayerPunchReported();

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
	Rng* rng = nullptr;
	Player* m_pPlayer = nullptr;
	BulletManager* m_pBulletManager = nullptr;

	EnemyState state = EnemyState::Patrol;

	// look around
	Direction movementDirectionAfterLookAround = Direction::Up;
	Direction movementDirectionBeforeLookAround = Direction::Up;
	const int LOOKAROUND_CHANCE = 50;

	// speed
	const float SPEED = 0.1f;
	const float SPEED_CHASE = 0.15f;

	// chase
	Direction chaseDirectionBeforeCollision = Direction::Up;
	bool chaseHasEverCollided = false;
	int chaseNoMovementCount = 0;

	// punch
	BoxAabb* m_boxAabb = nullptr;
	int m_debug_gotPunchedFrameCounter = 0;

	// HP
	const int MAX_HP = 3;
	int m_hp = MAX_HP;

	// LookAround
	float lookaroundTimer = 0.0f;
	const float LOOKAROUND_TIME = 500.0f;
	Direction lookAroundDirection = Direction::Up;
	bool isOneStageOfLookOutPlaying = false;
	int lookAroundChecksDone = 0;

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
	void Debug_PrintValues() const;
	float2 GetCenterPos() const;
};
