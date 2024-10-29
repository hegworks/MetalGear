#pragma once
#include "src/Animation/customAnimation.h"
#include "src/human/human.h"
#include "src/managers/room/roomChange.h"
#include "src/managers/room/roomChangeType.h"

class HudManager;
class BoxAabb;
class PointCollider;

constexpr int PLAYER_ANIMATION_COUNT = 8;

class Player : public Human
{
public:
	Player(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, AudioManager* pAudioManager, HudManager* pHudManager);
	~Player();
	virtual void Tick(float deltaTime);
#ifdef _DEBUG
	virtual void DrawColliders();
#endif

	// report
	RoomChangeType GetRoomChangeType() const { return m_newRoomChangeType; }
	bool ReportRoomChange();
	bool ReportWin() const;
	bool ReportLose() const;
	bool ReportPunch();

	// getter
	float2 GetPosition() const;
	float2 GetHalfHeightPosition() const { return float2{m_position.x, m_position.y + m_halfHeightSpriteSize.y}; }
	int2 GetFeetTilePosition() const;
	int2 GetFeetPos() const;
	BoxAabb* GetPunchBoxAabb() const { return m_punchBoxAabb; }
	BoxAabb* GetEnemyBulletBoxAabbTop() const { return m_enemyBulletBoxAabbTop; }
	BoxAabb* GetEnemyBulletBoxAabbBottom() const { return m_enemyBulletBoxAabbBottom; }
	float2 GetCenterPos() const;

	// else
	void RoomChangePos(const RoomChange& roomChange);
	void KeyDown(int glfwKey);
	void EnemyBulletCollided();
	void Reset();

private:
	// animation
	CustomAnimation animations[PLAYER_ANIMATION_COUNT] =
	{
		{AnimationType::Up, 6, 8 },
		{AnimationType::Down, 0, 2 },
		{AnimationType::Left, 3, 5 },
		{AnimationType::Right, 9, 11 },
		{AnimationType::PunchUp, 24, 24 },
		{AnimationType::PunchDown, 16, 16 },
		{AnimationType::PunchLeft, 20, 20 },
		{AnimationType::PunchRight, 28, 28 },
	};
	const float ANIMATION_UPDATE_TIME = 100.0f;
	float m_animationUpdateTimer = 0.0f;
	bool m_hasDirectionInput = false;

	// hurt animation
	Sprite* m_pHurtSprite = nullptr;
	Sprite* m_pNormalSprite = nullptr;
	bool m_isHurtAnimationPlaying = false;
	const float HURT_ANIMATION_TIME = 500.0f;
	float m_hurtAnimationTimer = 0;
	const float HURT_ANIMATION_INTERVAL = 50.0f;
	float m_hurtAnimationIntervalTimer = 0;

	// room change
	PointCollider* m_roomChangeCollider = nullptr;
	const int m_roomChangeColliderXOffset = -5;
	const int m_roomChangeColliderYOffset = -5;
	const float2 SPAWN_POS = {512,256};
	RoomChangeType m_newRoomChangeType = {};

	// punch
	BoxAabb* m_punchBoxAabb = nullptr;
	bool m_isPunchKeyDownAndHaveNotPunched = false;
	int m_debug_punchFrameCounter = 0;
	const float PUNCH_SIZE = 32;
	bool m_shouldStartPunchAnimation = false;
	const float PUNCH_ANIMATION_DURATION = 500.0f;
	float m_punchAnimationRemaining = 0;

	// enemy bullet
	BoxAabb* m_enemyBulletBoxAabbTop = nullptr;
	BoxAabb* m_enemyBulletBoxAabbBottom = nullptr;
	float2 m_spriteSize = {};
	float2 m_halfHeightSpriteSize = {};

	// HP
	const int HP_MAX = 5;
	int m_hp = HP_MAX;

	// references
	HudManager* m_pHudManager = nullptr;

	// functions
	void HandleInput();
	void UpdatePosition(float deltaTime);
	void UpdateColliders() const;
	void UpdateRoomChangeCollider() const;
	void UpdateEnemyBulletCollider() const;
	void UpdateAnimationState(float deltaTime);
	void Animate(float deltaTime);
	virtual void UpdateBroadPhaseCircleAabb() const;
	void CheckHurtAnimation(float deltaTime);
};
