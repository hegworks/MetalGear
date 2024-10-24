#pragma once
#include "direction.h"
#include "src/animation/animationType.h"
#include "src/tile/tileSet.h"

class AudioManager;
class CircleAabb;
class BoxCollider;
class SpriteStorage;
class LevelMaps;

class Human
{
public:
	Human(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, AudioManager* pAudioManager);

	virtual void Draw() const;
#ifdef _DEBUG
	virtual void DrawColliders() {}
#endif
	virtual void Tick(float /* deltatime */) {}
	CircleAabb* GetBroadPhaseCircleAabb() const { return m_broadPhaseCircleAabb; }
	Sprite* GetSprite() const { return  m_pSprite; }

protected:
	float2 m_position;

	Surface* m_pScreen = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	SpriteStorage* m_pSpriteStorage = nullptr;

	AnimationType m_currentAnimationState = AnimationType::Down;
	AnimationType m_lastAnimationState = AnimationType::Down;

	Sprite* m_pSprite = nullptr;

	Direction m_movementDirection = Direction::Down;

	float m_speed = 0;
	int m_animationFrame = 0;

	BoxCollider* m_tileBoxCollider = nullptr;
	const int tileBoxColliderXOffset = TILESET_TILEWIDTH - 8;
	const int tileBoxColliderYOffset = TILESET_TILEHEIGHT * 3 - 8;
	const int tileCollisionPreventPixels = 1;

	AudioManager* m_pAudioManager = nullptr;

	// broad-phase
	CircleAabb* m_broadPhaseCircleAabb = nullptr;
	const float BROAD_PHASE_CIRCLE_AABB_RADIUS = 96;
	virtual void UpdateBroadPhaseCircleAabb() const = 0;

	virtual void UpdateTileBoxCollider() const;
};
