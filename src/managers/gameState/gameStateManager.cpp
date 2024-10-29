#include "precomp.h"
#include "gameStateManager.h"

#include "src/audio/audioManager.h"
#include "src/human/player/player.h"
#include "src/managers/bullet/bulletManager.h"
#include "src/managers/enemy/enemySpawner.h"
#include "src/managers/gamescreen/loseScreen.h"
#include "src/managers/gamescreen/winScreen.h"
#include "src/managers/hud/hudManager.h"
#include "src/managers/room/roomFinder.h"
#include "src/radio/radio.h"
#include "src/tile/levelMap/levelMaps.h"
#include "src/tile/tileMap.h"

GameStateManager::GameStateManager(Surface* pScreen, WinScreen* pWinScreen, LoseScreen* pLoseScreen, Player* pPlayer, Radio* pRadio, RoomFinder* pRoomFinder, LevelMaps* pLevelMaps, EnemySpawner* pEnemySpawner, TileMap* pTileMap, BulletManager* pBulletManager, AudioManager* pAudioManager, HudManager* pHudManager)
{
	m_pScreen = pScreen;
	m_pWinScreen = pWinScreen;
	m_pLoseScreen = pLoseScreen;
	m_pPlayer = pPlayer;
	m_pRadio = pRadio;
	m_pRoomFinder = pRoomFinder;
	m_pLevelMaps = pLevelMaps;
	m_pEnemySpawner = pEnemySpawner;
	m_pTileMap = pTileMap;
	m_pBulletManager = pBulletManager;
	m_pAudioManager = pAudioManager;
	m_pHudManager = pHudManager;
}

void GameStateManager::Tick(float deltaTime)
{
	ChangeGameStateBasedOnReports();
	PassDownReport();
	PassDownTick(deltaTime);
}

void GameStateManager::Draw() const
{
	// Pass down Draw()
	switch(m_gameState)
	{
		case GameState::Intro:
			//TODO draw intro
			break;
		case GameState::Gameplay:
			m_pTileMap->DrawLevel(m_ppCurrentLevelTiles);
			m_pPlayer->Draw();
			m_pEnemySpawner->Draw();
			m_pBulletManager->Draw();
			m_pHudManager->Draw();
			break;
		case GameState::Win:
			m_pWinScreen->Draw(m_pScreen);
			break;
		case GameState::Lose:
			m_pLoseScreen->Draw(m_pScreen);
			break;
		case GameState::Radio:
			m_pRadio->Draw();
			m_pHudManager->Draw();
			break;
		default:
			throw exception("Invalid GameState");
	}
}

#ifdef _DEBUG
void GameStateManager::DrawColliders() const
{
	// Pass down DrawColliders()
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			m_pPlayer->DrawColliders();
			m_pTileMap->DrawLevel(m_ppCurrentLevelColliders);
			m_pEnemySpawner->DrawColliders();
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Radio:
			break;
		default:
			throw exception("Invalid GameState");
	}
}
#endif

void GameStateManager::KeyDown(int glfwKey)
{
	HandleGameStateChangeBasedOnKeyDown(glfwKey);
	PassDownKeyDown(glfwKey);
}

void GameStateManager::KeyUp(int glfwKey)
{
	// Pass down KeyUp()
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			m_pRadio->KeyUp(glfwKey);
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Radio:
			m_pRadio->KeyUp(glfwKey);
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::PassDownReport()
{
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			if(m_pPlayer->ReportRoomChange())
			{
				ChangeRoom(m_pPlayer->GetRoomChangeType());
			}
			if(m_pPlayer->ReportPunch())
			{
				m_pEnemySpawner->PlayerPunchReported();
			}
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Radio:
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::PassDownTick(float deltaTime)
{
	switch(m_gameState)
	{
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			m_pPlayer->Tick(deltaTime);
			m_pEnemySpawner->Tick(deltaTime);
			m_pBulletManager->Tick(deltaTime);
			break;
		case GameState::Radio:
			m_pRadio->Tick(deltaTime);
			break;
		default:
			throw exception("invalid game state");
	}
}

void GameStateManager::ChangeGameStateBasedOnReports()
{
	switch(m_gameState)
	{
		case GameState::Intro:
			//TODO play the real intro
			// if intro finished:
			m_pAudioManager->GameplayStarted();
			m_pRoomFinder->SetCurrentLevelId(STARTING_ROOM_ID);
			ChangeRoom();
			m_pPlayer->Reset();
			m_gameState = GameState::Gameplay;
			break;
		case GameState::Gameplay:
			if(m_pPlayer->ReportWin())
			{
				m_pAudioManager->Won();
				m_gameState = GameState::Win;
			}
			else if(m_pPlayer->ReportLose())
			{
				m_pAudioManager->Lost();
				m_gameState = GameState::Lose;
			}
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Radio:
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::HandleGameStateChangeBasedOnKeyDown(int glfwKey)
{
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			if(glfwKey == RADIO_KEY)
			{
				m_pRadio->Show(m_pRoomFinder->GetCurrentLevelId());
				m_gameState = GameState::Radio;
			}
			break;
		case GameState::Win:
		case GameState::Lose:
			if(glfwKey == RESTART_KEY)
			{
				m_gameState = GameState::Intro;
			}
			break;
		case GameState::Radio:
			if(glfwKey == RADIO_KEY)
			{
				m_pRadio->Hide();
				m_gameState = GameState::Gameplay;
			}
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::PassDownKeyDown(int glfwKey)
{
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			m_pPlayer->KeyDown(glfwKey);
			m_pRadio->KeyDown(glfwKey);
			break;
		case GameState::Win:
			break;
		case GameState::Lose:
			break;
		case GameState::Radio:
			m_pRadio->KeyDown(glfwKey);
			break;
		default:
			throw exception("Invalid GameState");
	}
}

/*
* TL;DR:
* this function is just resolving the RoomChange report by calling different classes.
* since I didn't want to pass every class to every other class and/or have 2-way references (a referencing b and b referencing a) in my code.
*
* Long explanation:
* this function needs to be here in game.cpp because there is no event handler in C++ without STL.
* this solution of calling methods on classes to check if whether something has happened or not, so
* then we can propagate (pass down) this event to our other classes, was given to me by David Jones. He said this is
* a common practice, and he uses this himself as well.
*
* the next best option was to make an event handler myself, but making systems like that (e.g. event subscription system,
* resizable arrays, or any feature from STL), even though may
* seem very tempting, but it is discouraged by all the teachers and I understand why.
*/
void GameStateManager::ChangeRoom(const RoomChangeType roomChangeType)
{
	if(roomChangeType != RoomChangeType::None)
	{
		const RoomChange newRoom = m_pRoomFinder->FindNextRoom(roomChangeType);
		m_pRoomFinder->SetCurrentLevelId(newRoom.nextRoomId);
		m_pPlayer->RoomChangePos(newRoom);
	}
	m_pLevelMaps->SetCurrentLevelId(m_pRoomFinder->GetCurrentLevelId());
	m_ppCurrentLevelTiles = m_pLevelMaps->GetLevelMapPointers();
	m_pLevelMaps->DeleteCurrentColliders();
	m_ppCurrentLevelColliders = m_pLevelMaps->GetLevelColliderPointers();
	m_pEnemySpawner->RoomChanged();
	m_pEnemySpawner->Spawn();
	m_pBulletManager->RoomChanged();
	m_pAudioManager->RoomChanged(m_pRoomFinder->GetCurrentLevelId());
}