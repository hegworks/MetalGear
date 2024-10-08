// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

#include "human/player/player.h"
#include "managers/bullet/bulletManager.h"
#include "managers/enemy/enemySpawner.h"
#include "managers/room/roomChangeStorage.h"
#include "managers/room/roomFinder.h"
#include "spriteStorage/spriteStorage.h"
#include "tile/tileMap.h"
#include "tile/tileSet.h"

void Game::Init()
{
	tileSet = new TileSet();
	tileMap = new TileMap(screen, tileSet);
	roomChangeStorage = new RoomChangeStorage;
	roomFinder = new RoomFinder(roomChangeStorage);
	levelMaps = new LevelMaps();
	spriteStorage = new SpriteStorage();
	player = new Player(screen, levelMaps, spriteStorage);
	bulletManager = new BulletManager(screen, levelMaps, player, spriteStorage);
	enemySpawner = new EnemySpawner(screen, levelMaps, spriteStorage, player, bulletManager);
	roomFinder->SetCurrentLevelId(2);
	ChangeRoom();
}

void Game::Tick(float deltaTime)
{
	// tileMap
	tileMap->DrawLevel(currentLevelTiles);

	// player
	player->Tick(deltaTime);
	player->Draw();
#ifdef _PHYSICS_DEBUG
	player->DrawColliders();
#endif

	// enemies
	for(int i = 0; i < enemySpawner->enemyCount; i++)
	{
		enemySpawner->enemies[i]->Tick(deltaTime);
		enemySpawner->enemies[i]->Draw();
	}

	bulletManager->Tick(deltaTime);
	bulletManager->Draw();

#ifdef _PHYSICS_DEBUG
	tileMap->DrawLevel(currentLevelColliders);

	for(int i = 0; i < enemySpawner->enemyCount; i++)
	{
		enemySpawner->enemies[i]->DrawColliders();
	}
#endif

	// room
	switch(RoomChangeType roomChangeType = player->ReportRoomChange())
	{
		case RoomChangeType::None:
			break;
		case RoomChangeType::RC0:
		case RoomChangeType::RC1:
		case RoomChangeType::RC2:
		case RoomChangeType::RC3:
		case RoomChangeType::RC4:
			RoomChange newRoom = roomFinder->FindNextRoom(roomChangeType);
			roomFinder->SetCurrentLevelId(newRoom.nextRoomId);
			player->RoomChangePos(newRoom);
			ChangeRoom();
			break;
		default:
			throw exception("Invalid room change type");
	}

	if(player->ReportPunch())
	{
		for(int i = 0; i < enemySpawner->enemyCount; i++)
		{
			enemySpawner->enemies[i]->PlayerPunchReported();
		}
	}
}

void Tmpl8::Game::KeyDown(int glfwKey)
{
	player->KeyDown(glfwKey);
}

void Game::ChangeRoom()
{
	levelMaps->SetCurrentLevelId(roomFinder->GetCurrentLevelId());
	currentLevelTiles = levelMaps->GetLevelMapPointers();
	currentLevelColliders = levelMaps->GetLevelColliderPointers();
	enemySpawner->Spawn();
}
