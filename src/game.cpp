// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

void Game::Init()
{
	tileSet = new TileSet();
	tileMap = new TileMap(screen, tileSet);
	roomChangeStorage = new RoomChangeStorage;
	roomFinder = new RoomFinder(roomChangeStorage);
	levelMaps = new LevelMaps();
	spriteStorage = new SpriteStorage();
	player = new Player(screen, levelMaps, spriteStorage);
	ChangeRoom();
}

void Game::Tick(float deltaTime)
{
	tileMap->DrawLevel(currentLevelTiles);
#ifdef _PHYSICS_DEBUG
	tileMap->DrawLevel(currentLevelColliders);
#endif

	player->Tick(deltaTime);
	player->Draw();
#ifdef _PHYSICS_DEBUG
	player->DrawColliders();
#endif

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
			ChangeRoom();
			player->RoomChangePos(newRoom);
			break;
		default:
			throw exception("Invalid room change type");
	}
}

void Game::ChangeRoom()
{
	levelMaps->SetCurrentLevelId(roomFinder->GetCurrentLevelId());
	currentLevelTiles = levelMaps->GetLevelMapPointers();
	currentLevelColliders = levelMaps->GetLevelColliderPointers();
}
