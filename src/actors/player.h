#pragma once
#include "direction.h"
#include "human.h"
#include "src/Animation/customAnimation.h"
#include "src/collider/boxCollider/boxCollider.h"
#include "src/tile/tileSet.h"

constexpr int PLAYER_ANIMATION_COUNT = 4;

class Player : public Human
{
public:
	Player(Surface* screen, LevelMaps* levelMaps);
	void Tick(float deltaTime) override;

private:
	CustomAnimation animations[PLAYER_ANIMATION_COUNT] =
	{
	{AnimationState::Up, 6, 8 },
	{AnimationState::Down, 0, 2 },
	{AnimationState::Left, 3, 5 },
	{AnimationState::Right, 9, 11 },
	};

	bool isIdle = true;

	const float ANIMATION_UPDATE_TIME = 100.0f;
	float animationUpdateTimer = 0.0f;
	Direction movementDirection = Direction::Down;

	BoxCollider* tileBoxCollider;
	const int tileBoxColliderXOffset = TILESET_TILEWIDTH - 8;
	const int tileBoxColliderYOffset = TILESET_TILEHEIGHT * 3 - 8;

	void HandleInput();
	void UpdatePosition(float deltaTime);
	void UpdateColliders() const;
	void UpdateAnimationState();
	void Animate(float deltaTime);
};
