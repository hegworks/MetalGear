﻿#include "precomp.h"
#include "bullet.h"

#include "src/collider/aabb/boxAabb/boxAabb.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/human/player/player.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"

Bullet::Bullet(int id, float2 startPos, float2 direction, Surface* pScreen, Player* pPlayer, SpriteStorage* pSpriteStorage, LevelMaps* pLevelMaps)
{
	m_id = id;
	m_pos = startPos;
	m_dir = direction;

	m_pScreen = pScreen;
	m_pPlayer = pPlayer;

	m_pSprite = pSpriteStorage->GetSpriteData(SpriteType::Bullet)->sprite;

	m_pPointCollider = new PointCollider(m_pScreen, pLevelMaps);
}

void Bullet::Tick(float deltaTime)
{
	if(!m_isActive) return;

	UpdatePointCollider();
	CheckPointCollider();
	CheckPlayerCollision();
	Move(deltaTime);
	CheckOutOfScreen();
}

void Bullet::Activate(const float2 startPos, const float2 direction)
{
	m_pos = startPos;
	m_dir = normalize(direction);
	m_isActive = true;
}

void Bullet::Deactivate()
{
	m_pos = {0,0};
	m_dir = {0,0};
	m_isActive = false;
}

void Bullet::Draw() const
{
	if(!m_isActive) return;

	m_pSprite->Draw(m_pScreen, static_cast<int>(m_pos.x), static_cast<int>(m_pos.y));

#ifdef _DEBUG
	m_pPointCollider->Draw(1);
#endif
}

void Bullet::UpdatePointCollider() const
{
	m_pPointCollider->UpdatePosition(m_pos + static_cast<float>(m_pSprite->GetWidth()) / 2.0f);
}

void Bullet::Move(const float deltaTime)
{
	m_pos += m_dir * m_speed * deltaTime;
}

void Bullet::CheckPointCollider()
{
	if(m_pPointCollider->IsSolid())
	{
		Deactivate();
	}
}

void Bullet::CheckPlayerCollision()
{
	if(m_pPlayer->GetEnemyBulletBoxAabb()->IsColliding(m_pos))
	{
		m_pPlayer->EnemyBulletCollided();
		Deactivate();
	}
}

void Bullet::CheckOutOfScreen()
{
	if(m_pos.x < 0 || m_pos.x > SCRWIDTH || m_pos.y < 0 || m_pos.y > SCRHEIGHT)
	{
		Deactivate();
	}
}