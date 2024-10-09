#pragma once

class LevelMaps;
class SpriteStorage;
class BulletManager;
class Player;
class PointCollider;

class Bullet
{
public:
	Bullet(int id, float2 startPos, float2 direction, Surface* pScreen, Player* pPlayer, SpriteStorage* pSpriteStorage, LevelMaps* pLevelMaps);
	void Tick(float deltaTime);
	void Activate(float2 startPos, float2 direction);
	void Deactivate();
	void Draw() const;

	int GetId() const { return m_id; }
	bool IsActive() const { return m_isActive; }

private:
	float2 m_pos{};
	float2 m_dir{};
	float m_speed = 0.25f;
	int m_id = -1;
	bool m_isActive = false;

	PointCollider* m_pPointCollider = nullptr;
	Player* m_pPlayer = nullptr;
	Surface* m_pScreen = nullptr;
	Sprite* m_pSprite = nullptr;

	void UpdatePointCollider() const;
	void Move(float deltaTime);
	void CheckPointCollider();
	void CheckPlayerCollision();
	void CheckOutOfScreen();
};
