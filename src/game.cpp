// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

#include "human/player/player.h"
#include "managers/bullet/bulletManager.h"
#include "managers/enemy/enemySpawner.h"
#include "managers/gamescreen/loseScreen.h"
#include "managers/gamescreen/winScreen.h"
#include "managers/gameState/gameStateManager.h"
#include "managers/room/roomChangeStorage.h"
#include "managers/room/roomFinder.h"
#include "spriteStorage/spriteStorage.h"
#include "tile/tileMap.h"
#include "tile/tileSet.h"

void Game::Init()
{
	m_tileSet = new TileSet();
	m_tileMap = new TileMap(screen, m_tileSet);
	m_roomChangeStorage = new RoomChangeStorage;
	m_roomFinder = new RoomFinder(m_roomChangeStorage);
	m_levelMaps = new LevelMaps();
	m_spriteStorage = new SpriteStorage();
	m_player = new Player(screen, m_levelMaps, m_spriteStorage);
	m_bulletManager = new BulletManager(screen, m_levelMaps, m_player, m_spriteStorage);
	m_enemySpawner = new EnemySpawner(screen, m_levelMaps, m_spriteStorage, m_player, m_bulletManager);
	m_winScreen = new WinScreen();
	m_loseScreen = new LoseScreen();
	m_gameStateManager = new GameStateManager(screen, m_winScreen, m_loseScreen, m_player);
}

void Game::Tick(const float deltaTime)
{
	if(m_gameStateManager->GetGameState() == GameState::Lose || m_gameStateManager->GetGameState() == GameState::Win)
		return;

	if(m_gameStateManager->GetGameState() == GameState::Intro)
	{
		//TODO play the real intro
		m_roomFinder->SetCurrentLevelId(0);
		ChangeRoom();
		m_player->Reset();
		m_gameStateManager->IntroFinished();
	}

	// tileMap
	m_tileMap->DrawLevel(m_currentLevelTiles);

	// player
	m_player->Tick(deltaTime);
	m_player->Draw();
#ifdef _PHYSICS_DEBUG
	m_player->DrawColliders();
#endif

	// enemies
	m_enemySpawner->Tick(deltaTime);
	m_enemySpawner->Draw();

	// bullets
	m_bulletManager->Tick(deltaTime);
	m_bulletManager->Draw();

#ifdef _PHYSICS_DEBUG
	m_tileMap->DrawLevel(m_currentLevelColliders);
	m_enemySpawner->DrawColliders();
#endif

	// room
	switch(RoomChangeType roomChangeType = m_player->ReportRoomChange())
	{
		case RoomChangeType::None:
			break;
		case RoomChangeType::RC0:
		case RoomChangeType::RC1:
		case RoomChangeType::RC2:
		case RoomChangeType::RC3:
		case RoomChangeType::RC4:
			const RoomChange newRoom = m_roomFinder->FindNextRoom(roomChangeType);
			m_roomFinder->SetCurrentLevelId(newRoom.nextRoomId);
			m_player->RoomChangePos(newRoom);
			ChangeRoom();
			break;
		default:
			throw exception("Invalid room change type");
	}

	if(m_player->ReportPunch())
	{
		m_enemySpawner->PlayerPunchReported();
	}

	m_gameStateManager->Tick(deltaTime);
	m_gameStateManager->Draw();
}

void Game::KeyDown(const int glfwKey)
{
	m_player->KeyDown(glfwKey);
	m_gameStateManager->KeyDown(glfwKey);
}

void Game::ChangeRoom()
{
	m_levelMaps->SetCurrentLevelId(m_roomFinder->GetCurrentLevelId());
	m_currentLevelTiles = m_levelMaps->GetLevelMapPointers();
	m_currentLevelColliders = m_levelMaps->GetLevelColliderPointers();
	m_enemySpawner->Spawn();
	m_bulletManager->RoomChanged();
}
