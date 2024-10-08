#pragma once
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"
#include "src/managers/room/roomChange.h"
#include "src/managers/room/roomChangeType.h"

class BoxAabb;
class PointCollider;

constexpr int PLAYER_ANIMATION_COUNT = 4;

class Player : public Human
{
public:
	Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
	virtual void Tick(float deltaTime);
	virtual void DrawColliders();

	// report
	RoomChangeType ReportRoomChange() const;
	bool ReportPunch();

	// getter
	float2 GetPosition() const;
	int2 GetFeetTilePosition() const;
	int2 GetFeetPos() const;
	BoxAabb* GetPunchBoxAabb() const { return m_punchBoxAabb; }

	// else
	void RoomChangePos(RoomChange roomChange);
	void KeyDown(int glfwKey);

private:
	// animation
	CustomAnimation animations[PLAYER_ANIMATION_COUNT] =
	{
		{AnimationState::Up, 6, 8 },
		{AnimationState::Down, 0, 2 },
		{AnimationState::Left, 3, 5 },
		{AnimationState::Right, 9, 11 },
	};
	const float ANIMATION_UPDATE_TIME = 100.0f;
	float animationUpdateTimer = 0.0f;
	bool isIdle = true;

	// room change
	PointCollider* roomChangeCollider = nullptr;
	const int roomChangeColliderXOffset = -5;
	const int roomChangeColliderYOffset = -5;

	// punch
	BoxAabb* m_punchBoxAabb = nullptr;
	bool m_isPunchKeyDownAndHaveNotPunched = false;
	int m_debug_punchFrameCounter = 0;


	// functions
	void HandleInput();
	void UpdatePosition(float deltaTime);
	void UpdateColliders() const;
	void UpdateRoomChangeCollider() const;
	void UpdateAnimationState();
	void Animate(float deltaTime);
};
