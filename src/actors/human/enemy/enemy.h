#pragma once
#include "src/actors/direction.h"
#include "src/actors/human/human.h"
#include "src/Animation/customAnimation.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/tile/tileSet.h"

constexpr int ENEMY_ANIMATION_COUNT = 4;

class Enemy : public Human
{
public:
	Enemy(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, float2 spawnPos, Direction spawnDir);
	void Tick(float deltaTime) override;
	void DrawColliders() const override;

private:
	// colliders
	PointCollider* patrolCollider = nullptr;
	const int patrolColliderXOffset = 0;
	const int patrolColliderYOffset = TILESET_TILEWIDTH / 2;

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
	Direction movementDirection = Direction::Down;

	// functions
	void UpdateColliders();
	void UpdatePatrolCollider() const;
	void CheckPatrolCollider();
	void UpdatePosition(float deltaTime);
	void UpdateAnimationState();
	void Animate(float deltaTime);
};
