#pragma once
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"
#include "src/managers/room/roomChange.h"
#include "src/managers/room/roomChangeType.h"

class BoxAabb;
class PointCollider;

constexpr int PLAYER_ANIMATION_COUNT = 8;

class Player : public Human
{
public:
	Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage);
	virtual void Tick(float deltaTime);
#ifdef _PHYSICS_DEBUG
	virtual void DrawColliders();
#endif

	// report
	RoomChangeType ReportRoomChange() const;
	bool ReportPunch();

	// getter
	float2 GetPosition() const;
	int2 GetFeetTilePosition() const;
	int2 GetFeetPos() const;
	BoxAabb* GetPunchBoxAabb() const { return m_punchBoxAabb; }
	BoxAabb* GetEnemyBulletBoxAabb() const { return m_enemyBulletBoxAabb; }
	float2 GetCenterPos() const;

	// else
	void RoomChangePos(const RoomChange& roomChange);
	void KeyDown(int glfwKey);
	void EnemyBulletCollided();

private:
	// animation
	CustomAnimation animations[PLAYER_ANIMATION_COUNT] =
	{
		{AnimationState::Up, 6, 8 },
		{AnimationState::Down, 0, 2 },
		{AnimationState::Left, 3, 5 },
		{AnimationState::Right, 9, 11 },
		{AnimationState::PunchUp, 24, 24 },
		{AnimationState::PunchDown, 16, 16 },
		{AnimationState::PunchLeft, 20, 20 },
		{AnimationState::PunchRight, 28, 28 },
	};
	const float ANIMATION_UPDATE_TIME = 100.0f;
	float m_animationUpdateTimer = 0.0f;
	bool m_hasDirectionInput = false;

	// room change
	PointCollider* m_roomChangeCollider = nullptr;
	const int m_roomChangeColliderXOffset = -5;
	const int m_roomChangeColliderYOffset = -5;

	// punch
	BoxAabb* m_punchBoxAabb = nullptr;
	bool m_isPunchKeyDownAndHaveNotPunched = false;
	int m_debug_punchFrameCounter = 0;
	const float PUNCH_SIZE = 32;
	bool m_shouldStartPunchAnimation = false;
	const float PUNCH_ANIMATION_DURATION = 500.0f;
	float m_punchAnimationRemaining = 0;

	// enemy bullet
	BoxAabb* m_enemyBulletBoxAabb = nullptr;

	// HP
	const int HP_MAX = 5;
	int m_hp = HP_MAX;

	// functions
	void HandleInput();
	void UpdatePosition(float deltaTime);
	void UpdateColliders() const;
	void UpdateRoomChangeCollider() const;
	void UpdateEnemyBulletCollider() const;
	void UpdateAnimationState(float deltaTime);
	void Animate(float deltaTime);
};
