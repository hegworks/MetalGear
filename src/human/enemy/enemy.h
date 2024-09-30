#pragma once
#include "enemyState.h"
#include "src/Animation/customAnimation.h"
#include "src/human/direction.h"
#include "src/human/human.h"
#include "src/tile/tileSet.h"

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
	virtual void DrawColliders() const;

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

	// else
	Direction movementDirection = Direction::Up;
	Direction movementDirectionAfterLookAround = Direction::Up;
	Direction movementDirectionBeforeLookAround = Direction::Up;
	const float SPEED = 0.1f;
	const int LOOKAROUND_CHANCE = 50;
	Rng* rng = nullptr;
	EnemyState state = EnemyState::Patrol;
	Player* m_pPlayer = nullptr;

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
	void CheckPatrolCollider();
	void Lookaround(float deltaTime);
	void MoveInDirection(float deltaTime);
	void UpdateAnimationState();
	void Animate(float deltaTime);
	void ChasePlayer(float deltaTime);
};
