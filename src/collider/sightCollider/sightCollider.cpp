#include "precomp.h"
#include "sightCollider.h"
#include "src/collider/pointCollider/pointCollider.h"
#include "src/human/player/player.h"
#include "src/tile/tileSet.h"

SightCollider::SightCollider(Surface* pScreen, LevelMaps* pLevelMaps, Player* pPlayer) : Collider(pScreen, pLevelMaps)
{
	m_pPlayer = pPlayer;

	for(int i = 0; i < SIGHT_COLL_SIZE; i++)
	{
		m_pPoints[i] = new PointCollider(pScreen, pLevelMaps);
	}
}

void SightCollider::UpdatePosition(const int2 startPos, Direction dir)
{
	m_dir = dir;
	int2 dir_val = {0,0};
	switch(dir)
	{
		case Direction::Up:
			dir_val = {0,-1};
			break;
		case Direction::Down:
			dir_val = {0,1};
			break;
		case Direction::Left:
			dir_val = {-1,0};
			break;
		case Direction::Right:
			dir_val = {1,0};
			break;
	}

	for(int i = 0; i < SIGHT_COLL_SIZE; i++)
	{
		m_pPoints[i]->UpdatePosition(startPos + i * dir_val * TILESET_TILEWIDTH);
	}
}

void SightCollider::Draw(const int visualSize, const int color)
{
	for(int i = 0; i < SIGHT_COLL_SIZE; i++)
	{
		if(!IsOutOfScreen(m_pPoints[i]->GetPos()))
		{
			m_pPoints[i]->Draw(visualSize, color);
		}
	}
}

bool SightCollider::IsPlayerInSight()
{
	int2 playerTilePos = m_pPlayer->GetFeetTilePosition();
	int2 sightStartTilePos = m_pLevelMaps->GetTilePos(m_pPoints[0]->GetPos());

	if(playerTilePos.y != sightStartTilePos.y && playerTilePos.x != sightStartTilePos.x)
	{
		return false;
	}

	if((m_dir == Direction::Left && playerTilePos.x > sightStartTilePos.x) ||
	   (m_dir == Direction::Right && playerTilePos.x < sightStartTilePos.x) ||
	   (m_dir == Direction::Up && playerTilePos.y > sightStartTilePos.y) ||
	   (m_dir == Direction::Down && playerTilePos.y < sightStartTilePos.y))
	{
		return false;
	}

	for(int i = 0; i < SIGHT_COLL_SIZE; i++)
	{
		if(!IsOutOfScreen(m_pPoints[i]->GetPos()))
		{
			if(m_pLevelMaps->IsSolid(m_pPoints[i]->GetPos()))
			{
				return false;
			}

			if(playerTilePos == m_pLevelMaps->GetTilePos(m_pPoints[i]->GetPos()))
			{
				return true;
			}
		}
	}
	return false;
}

bool SightCollider::IsOutOfScreen(int2 pos) const
{
	return pos.x < TILESET_TILEWIDTH || pos.x > SCRWIDTH - TILESET_TILEWIDTH || pos.y < TILESET_TILEWIDTH || pos.y > SCRHEIGHT - TILESET_TILEHEIGHT;
}
