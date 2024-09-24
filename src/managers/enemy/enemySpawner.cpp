#include "precomp.h"
#include "enemySpawner.h"

#include "src/tile/tileSet.h"

EnemySpawner::EnemySpawner(Surface* screen, LevelMaps* levelMaps, SpriteStorage* spriteStorage)
{
	this->screen = screen;
	this->levelMaps = levelMaps;
	this->spriteStorage = spriteStorage;
}

bool EnemySpawner::Spawn()
{
	for(int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i] = nullptr;
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
					float2 spawnPos = float2(j * TILESET_TILEWIDTH, i * TILESET_TILEHEIGHT - 96);
					enemies[enemyCount] = new Enemy(screen, levelMaps, spriteStorage, spawnPos, spawnDir);
					enemyCount++;
					if(enemyCount >= MAX_ENEMIES)
					{
						return true;
					}
				}
			}
		}
	}
	return enemyCount > 0;
}
