#pragma once
#include "enemyState.h"
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"

class BoxAabb;
class Player;
class SightCollider;
class PointCollider;
class Rng;

constexpr int ENEMY_ANIMATION_COUNT = 4;

class Enemy : public Human
{
public:
	Enemy(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, float2 spawnPos, Direction spawnDir, Player* pPlayer);
	virtual void Tick(float deltaTime);
	virtual void DrawColliders();
	virtual void Draw() const;
	void PlayerPunchReported();

private:
	// colliders
	PointCollider* patrolCollider = nullptr;
	const int patrolColliderXOffset = 0;
	const int patrolColliderYOffset = TILESET_TILEWIDTH / 2;

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
	bool m_debug_gotPunched = false;
	int m_debug_gotPunchedFrameCounter = 0;
	int m_debug_gotPunchedFrameCount = 10;
	BoxAabb* m_boxAabb = nullptr;

	// HP
	const int MAX_HP = 3;
	int m_hp = MAX_HP;

	// LookAround
	float lookaroundTimer = 0.0f;
	const float LOOKAROUND_TIME = 500.0f;
	Direction lookAroundDirection = Direction::Up;
	bool isOneStageOfLookOutPlaying = false;
	int lookAroundChecksDone = 0;

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
	int2 GetSightColliderPos() const;
	void UpdateBoxAabb() const;
};
