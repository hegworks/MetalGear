#pragma once
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"
#include "src/managers/room/roomChange.h"
#include "src/managers/room/roomChangeType.h"

class PointCollider;

constexpr int PLAYER_ANIMATION_COUNT = 4;

class Player : public Human
{
public:
	Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
	void Tick(float deltaTime) override;
	RoomChangeType ReportRoomChange() const;
	void RoomChangePos(RoomChange roomChange);
	void DrawColliders() const override;
	float2 GetPosition() const;
	int2 GetFeetTilePosition() const;

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

	PointCollider* roomChangeCollider = nullptr;
	const int roomChangeColliderXOffset = -5;
	const int roomChangeColliderYOffset = -5;

	void HandleInput();
	void UpdatePosition(float deltaTime);
	void UpdateColliders() const;
	void UpdateRoomChangeCollider() const;
	void UpdateAnimationState();
	void Animate(float deltaTime);
};
