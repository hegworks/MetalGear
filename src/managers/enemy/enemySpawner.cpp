#include "precomp.h"
#include "enemySpawner.h"

#include "src/tile/tileSet.h"

EnemySpawner::EnemySpawner(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage, Player* player)
{
	this->screen = screen;
	this->levelMaps = levelMaps;
	this->spriteStorage = spriteStorage;
	this->player = player;
}

bool EnemySpawner::Spawn()
{
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i] = nullptr;
	}

	bool isExceptionLevel4 = levelMaps->GetCurrentLevelId() == 4;
	bool isPlayerCloserToBottom = player->GetPosition().y > SCRHEIGHT / 2;
	bool skipLeftSpawn = false;
	bool skipRightSpawn = false;

	if(isExceptionLevel4)
	{
		skipLeftSpawn = !isPlayerCloserToBottom;
		skipRightSpawn = !skipLeftSpawn;
	}

	enemyCount = 0;

	int** levelColls = levelMaps->GetLevelColliderPointers();
	for(int i = 0; i < LEVELMAP_ROWS; i++)
	{
		for(int j = 0; j < LEVELMAP_COLS; j++)
		{
			int tileIndex = levelColls[i][j];
			if(tileIndex != -1)
			{
				TileType tileType = levelMaps->GetTileType(levelColls[i][j]);

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
						float2 spawnPos = float2(j * TILESET_TILEWIDTH, i * TILESET_TILEHEIGHT - 96);
						enemies[enemyCount] = new Enemy(screen, levelMaps, spriteStorage, spawnPos, spawnDir, player);
						enemyCount++;
						if(enemyCount >= MAX_ENEMIES)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return enemyCount > 0;
}
