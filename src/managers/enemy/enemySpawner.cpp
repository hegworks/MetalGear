#include "precomp.h"
#include "enemySpawner.h"

#include "src/audio/audioManager.h"
#include "src/tile/levelMap/levelMaps.h"
#include "src/tile/tileSet.h"

EnemySpawner::EnemySpawner(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager)
{
	m_screen = pScreen;
	m_levelMaps = pLevelMaps;
	m_spriteStorage = pSpriteStorage;
	m_player = pPlayer;
	m_bulletManager = pBulletManager;
	m_audioManager = pAudioManager;
}

void EnemySpawner::Tick(const float deltaTime)
{
	if(!m_hasAlertedAllInRoom)
	{
		bool isOneEnemyAlerted = false;
		for(int i = 0; i < m_enemyCount; ++i)
		{
			if(m_enemies[i]->ReportIsAlerted())
			{
				isOneEnemyAlerted = true;
			}
		}
		for(int i = 0; i < m_enemyCount; ++i)
		{
			if(isOneEnemyAlerted)
			{
				m_enemies[i]->OneEnemyAlarmedReport();
			}
		}
		if(isOneEnemyAlerted)
		{
			m_hasAlertedAllInRoom = true;
			m_audioManager->EnemyAlerted();
		}
	}

	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->Tick(deltaTime);
	}
}

void EnemySpawner::Draw() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->Draw();
	}
}

#ifdef _DEBUG
void EnemySpawner::DrawColliders() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->DrawColliders();
	}
}
#endif

bool EnemySpawner::Spawn()
{
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		m_enemies[i] = nullptr;
	}

	bool isExceptionLevel4 = m_levelMaps->GetCurrentLevelId() == 4;
	bool isPlayerCloserToBottom = m_player->GetPosition().y > SCRHEIGHT / 2;
	bool skipLeftSpawn = false;
	bool skipRightSpawn = false;

	if(isExceptionLevel4)
	{
		skipLeftSpawn = !isPlayerCloserToBottom;
		skipRightSpawn = !skipLeftSpawn;
	}

	m_enemyCount = 0;

	int** levelColls = m_levelMaps->GetLevelColliderPointers();
	for(int i = 0; i < LEVELMAP_ROWS; i++)
	{
		for(int j = 0; j < LEVELMAP_COLS; j++)
		{
			int tileIndex = levelColls[i][j];
			if(tileIndex != -1)
			{
				const TileType tileType = m_levelMaps->GetTileType(levelColls[i][j]);

				if(tileType == TileType::ESD || tileType == TileType::ESL || tileType == TileType::ESR || tileType == TileType::ESU)
				{
					Direction spawnDir;
					switch(tileType)
					{
						case TileType::ESD:
							spawnDir = Direction::Down;
							break;
						case TileType::ESL:
							spawnDir = Direction::Left;
							break;
						case TileType::ESR:
							spawnDir = Direction::Right;
							break;
						case TileType::ESU:
							spawnDir = Direction::Up;
							break;
						default:
							throw exception("Invalid tile type");
					}
					if(!isExceptionLevel4 ||
					   (spawnDir == Direction::Up || spawnDir == Direction::Down) ||
					   (spawnDir == Direction::Left && !skipLeftSpawn) ||
					   spawnDir == Direction::Right && !skipRightSpawn)
					{
						float2 spawnPos = {static_cast<float>(j * TILESET_TILEWIDTH), static_cast<float>(i * TILESET_TILEHEIGHT - 96)};
						m_enemies[m_enemyCount] = new Enemy(m_screen, m_levelMaps, m_spriteStorage, spawnPos, spawnDir, m_player, m_bulletManager);
						m_enemyCount++;
						if(m_enemyCount >= MAX_ENEMIES)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return m_enemyCount > 0;
}

void EnemySpawner::PlayerPunchReported() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->PlayerPunchReported();
	}
}

void EnemySpawner::RoomChanged()
{
	m_hasAlertedAllInRoom = false;
}
