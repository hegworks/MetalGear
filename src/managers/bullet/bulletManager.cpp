#include "precomp.h"
#include "bulletManager.h"

#include "src/bullet/bullet.h"

BulletManager::BulletManager(Surface* pScreen, LevelMaps* pLevelMaps, Player* pPlayer, SpriteStorage* pSpriteStorage)
{
	m_pScreen = pScreen;
	m_pLevelMaps = pLevelMaps;
	m_pPlayer = pPlayer;

	const float2 defaultStartPos = {200,200};
	const float2 defaultDir = {0,0};

	for(int i = 0; i < MAX_BULLETS; ++i)
	{
		m_pBullets[i] = new Bullet(i, defaultStartPos, defaultDir, m_pScreen, m_pPlayer, this, pSpriteStorage);
	}
}

void BulletManager::Tick(float deltaTime)
{
	for(int i = 0; i < MAX_BULLETS; ++i)
	{
		m_pBullets[i]->Tick(deltaTime);

#ifdef _DEBUG
		if(m_pBullets[i]->IsActive())
		{
			m_pScreen->Circle(i * 50 + 25, 60, 25, 0xff0000);
			//m_pScreen->Box(i * 30 + i, 0, i * 30 + 29 + i, 30, 0xff0000);
		}
		else
		{
			m_pScreen->Circle(i * 50 + 25, 60, 25, 0x00ff00);
			//m_pScreen->Box(i * 30 + i, 0, i * 30 + 29 + i, 30, 0x00ff00);
		}
#endif
	}
}

void BulletManager::Draw() const
{
	for(int i = 0; i < MAX_BULLETS; ++i)
	{
		m_pBullets[i]->Draw();
	}
}

Bullet* BulletManager::SpawnNewBullet(const float2 startPos, const float2 direction)
{
	Bullet* newBullet = GetFirstInactiveBullet();
	newBullet->Activate(startPos, direction);
	return newBullet;
}

void BulletManager::DeactivateBullet(int bulletIndex)
{
}

Bullet* BulletManager::GetFirstInactiveBullet() const
{
	for(int i = 0; i < MAX_BULLETS; ++i)
	{
		if(!m_pBullets[i]->IsActive())
		{
			return m_pBullets[i];
		}
	}
	throw exception("No inactive bullet found");
}
