#include "precomp.h"
#include "bullet.h"

#include "src/collider/aabb/boxAabb/boxAabb.h"
#include "src/collider/aabb/circleAabb/circleAabb.h"
#include "src/collider/pixelPerfect/pixelPerfectCollisionChecker.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/human/player/player.h"
#include "src/spriteStorage/spriteStorage.h"
#include "src/spriteStorage/spriteType.h"


Bullet::Bullet(int id, float2 startPos, float2 direction, Surface* pScreen, Player* pPlayer, SpriteStorage* pSpriteStorage, LevelMaps* pLevelMaps, PixelPerfectCollisionChecker* pPixelPerfectCollisionChecker)
{
	m_id = id;
	m_pos = startPos;
	m_dir = direction;

	m_pScreen = pScreen;
	m_pPlayer = pPlayer;
	m_pPixelPerfectCollisionChecker = pPixelPerfectCollisionChecker;
	m_pLevelMaps = pLevelMaps;

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

	UpdatePointCollider();
	m_wasInWallWhenSpawned = m_pPointCollider->IsSolid();
	if(m_wasInWallWhenSpawned)
	{
		m_spawnedInWallTileRow = m_pLevelMaps->GetTilePos(m_pPointCollider->GetPos()).y;
		const float2 oneTileLowerPos = m_pPointCollider->GetPos() + float2{0.0f, TILESET_TILEHEIGHT};
		m_wasOneTileLowerSolidWhenSpawned = m_pLevelMaps->IsSolid(oneTileLowerPos);
	}

	m_isActive = true;
}

void Bullet::Deactivate()
{
	m_pos = {0,0};
	m_dir = {0,0};
	m_wasInWallWhenSpawned = false;
	m_spawnedInWallTileRow = -1;
	m_wasOneTileLowerSolidWhenSpawned = false;
	m_hasPassedANonSolid = false;
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
	if(!m_pPointCollider->IsSolid())
	{
		m_hasPassedANonSolid = true;
		return;
	}

	if(!m_hasPassedANonSolid && m_wasInWallWhenSpawned)
	{
		const int tileRow = m_pLevelMaps->GetTilePos(m_pPointCollider->GetPos()).y;

		if(tileRow == m_spawnedInWallTileRow)
		{
			return;
		}

		if(m_wasOneTileLowerSolidWhenSpawned && tileRow == m_spawnedInWallTileRow + 1)
		{
			return;
		}
	}

	Deactivate();
}

void Bullet::CheckPlayerCollision()
{
	// broad-phase
	if(!m_pPlayer->GetBroadPhaseCircleAabb()->IsColliding(m_pPointCollider->GetPos()))
	{
		return;
	}

#ifdef _DEBUG
	const float2 centerPos = m_pPointCollider->GetPos();
	const int2 centerPosInt = {static_cast<int>(centerPos.x), static_cast<int>(centerPos.y)};
	m_pScreen->Circle(centerPosInt.x, centerPosInt.y, 7, 0x00ff00);
#endif

	if(m_pPixelPerfectCollisionChecker->IsColliding(m_pPlayer->GetSprite(), m_pSprite, m_pPlayer->GetPosition(), m_pos, m_pPlayer->GetSprite()->GetCurrentFrame(), 0))
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
