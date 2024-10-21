// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

#include "collider/pixelPerfect/pixelPerfectCollisionChecker.h"
#include "human/player/player.h"
#include "managers/bullet/bulletManager.h"
#include "managers/enemy/enemySpawner.h"
#include "managers/gamescreen/loseScreen.h"
#include "managers/gamescreen/winScreen.h"
#include "managers/gameState/gameStateManager.h"
#include "managers/room/roomChangeStorage.h"
#include "managers/room/roomFinder.h"
#include "radio/radio.h"
#include "spriteStorage/spriteStorage.h"
#include "textRenderer/textRenderer.h"
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
	m_pixelPerfectCollisionChecker = new PixelPerfectCollisionChecker(screen);
	m_bulletManager = new BulletManager(screen, m_levelMaps, m_player, m_spriteStorage, m_pixelPerfectCollisionChecker);
	m_enemySpawner = new EnemySpawner(screen, m_levelMaps, m_spriteStorage, m_player, m_bulletManager);
	m_winScreen = new WinScreen();
	m_loseScreen = new LoseScreen();
	m_fontTextRenderer = new TextRenderer(screen, "assets/graphics/font.png", 41, 2, 4, FontTextRendererCharToIndex);
	m_radio = new Radio(screen, m_fontTextRenderer);
	m_gameStateManager = new GameStateManager(screen, m_winScreen, m_loseScreen, m_player, m_radio, m_roomFinder);
}

void Game::Tick(const float deltaTime)
{
	// Handle GameState----------
	switch(m_gameStateManager->GetGameState())
	{
		case GameState::Win:
		case GameState::Lose:
			return;
		case GameState::Intro:
			//TODO play the real intro
			m_roomFinder->SetCurrentLevelId(1);
			ChangeRoom();
			m_player->Reset();
			m_gameStateManager->IntroFinished();
			break;
		case GameState::Gameplay:
			// execute everything below the switch case
			break;
		case GameState::Radio:
			m_gameStateManager->Tick(deltaTime);
			m_gameStateManager->Draw();
			return;
		default:
			throw exception("invalid game state");
	}
	// ----------Handle GameState


	// Tick()----------
	m_player->Tick(deltaTime);
	m_enemySpawner->Tick(deltaTime);
	m_bulletManager->Tick(deltaTime);
	m_gameStateManager->Tick(deltaTime);
	m_radio->Tick(deltaTime);
	// ----------Tick()


	// Reports/Events---------- check the comment before ChangeRoom() in this class
	if(m_player->ReportRoomChange())
	{
		ChangeRoom(m_player->GetRoomChangeType());
	}

	if(m_player->ReportPunch())
	{
		m_enemySpawner->PlayerPunchReported();
	}
	// ----------Reports/Events


	// Draw()----------
	m_tileMap->DrawLevel(m_currentLevelTiles);
	m_player->Draw();
	m_enemySpawner->Draw();
	m_bulletManager->Draw();
	m_gameStateManager->Draw();
	m_fontTextRenderer->DrawText("hello***\nnew\nworld\nnnn\nnnn", 5, 5, 4);
	m_fontTextRenderer->DrawText("new", 5, 200, 2);
	m_fontTextRenderer->DrawText("world", 5, 300, 6);
	m_radio->Draw();
	// ----------Draw()


	// Debug----------
#ifdef _DEBUG
	m_player->DrawColliders();
	m_tileMap->DrawLevel(m_currentLevelColliders);
	m_enemySpawner->DrawColliders();
#endif
	// ----------Debug
}

void Game::KeyDown(const int glfwKey)
{
	m_player->KeyDown(glfwKey);
	m_gameStateManager->KeyDown(glfwKey);
	m_radio->KeyDown(glfwKey);
}

void Game::KeyUp(int glfwKey)
{
	m_radio->KeyUp(glfwKey);
}

/*
* this function needs to be here in game.cpp because there is no event handler in C++ without STL.
* this solution of calling methods on classes to check if whether something has happened or not, so
* then we can propagate this event to our other classes, was given to me by David Jones. He said this is
* a common practice, and he uses this himself too.
*
* the next best option was to make an event handler myself, but making systems like that (e.g. event subscription system,
* resizable arrays, or any feature from STL), even though may
* seem very tempting, but it is discouraged by all the teachers and I understand why.
*/
void Game::ChangeRoom(const RoomChangeType roomChangeType)
{
	if(roomChangeType != RoomChangeType::None)
	{
		const RoomChange newRoom = m_roomFinder->FindNextRoom(roomChangeType);
		m_roomFinder->SetCurrentLevelId(newRoom.nextRoomId);
		m_player->RoomChangePos(newRoom);
	}
	m_levelMaps->SetCurrentLevelId(m_roomFinder->GetCurrentLevelId());
	m_currentLevelTiles = m_levelMaps->GetLevelMapPointers();
	m_currentLevelColliders = m_levelMaps->GetLevelColliderPointers();
	m_enemySpawner->Spawn();
	m_bulletManager->RoomChanged();
}
