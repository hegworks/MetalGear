#include "precomp.h"
#include "bullet.h"

#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"

Bullet::Bullet(int id, float2 startPos, float2 direction, Surface* pScreen, Player* pPlayer, BulletManager* pBulletManager, SpriteStorage* pSpriteStorage)
{
	m_id = id;
	m_pos = startPos;
	m_dir = direction;

	m_pScreen = pScreen;
	m_pPlayer = pPlayer;
	m_pBulletManager = pBulletManager;

	m_pSprite = pSpriteStorage->GetSpriteData(SpriteType::Bullet)->sprite;
}

void Bullet::Tick(float deltaTime)
{
	if(!m_isActive) return;

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
}

void Bullet::Move(const float deltaTime)
{
	m_pos += m_dir * m_speed * deltaTime;
}

void Bullet::CheckOutOfScreen()
{
	if(m_pos.x < 0 || m_pos.x > SCRWIDTH || m_pos.y < 0 || m_pos.y > SCRHEIGHT)
	{
		Deactivate();
	}
}
