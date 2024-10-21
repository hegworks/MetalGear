#include "precomp.h"
#include "gameStateManager.h"

#include "src/human/player/player.h"
#include "src/managers/gamescreen/loseScreen.h"
#include "src/managers/gamescreen/winScreen.h"
#include "src/managers/room/roomFinder.h"
#include "src/radio/radio.h"

GameStateManager::GameStateManager(Surface* pScreen, WinScreen* pWinScreen, LoseScreen* pLoseScreen, Player* pPlayer, Radio* pRadio, RoomFinder* pRoomFinder)
{
	m_pScreen = pScreen;
	m_pWinScreen = pWinScreen;
	m_pLoseScreen = pLoseScreen;
	m_pPlayer = pPlayer;
	m_pRadio = pRadio;
	m_pRoomFinder = pRoomFinder;
}

void GameStateManager::Tick(float deltaTime)
{
	switch(m_gameState)
	{
		case GameState::Intro:
			break;
		case GameState::Gameplay:
			if(m_pPlayer->ReportWin())
			{
				m_gameState = GameState::Win;
			}
			else if(m_pPlayer->ReportLose())
			{
				m_gameState = GameState::Lose;
			}
			break;
		case GameState::Win:
		case GameState::Lose:
			break;
		case GameState::Radio:
			m_pRadio->Tick(deltaTime);
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::Draw() const
{
	switch(m_gameState)
	{
		case GameState::Intro:
		case GameState::Gameplay:
			break;
		case GameState::Win:
			m_pWinScreen->Draw(m_pScreen);
			break;
		case GameState::Lose:
			m_pLoseScreen->Draw(m_pScreen);
			break;
		case GameState::Radio:
			m_pRadio->Draw();
			break;
		default:
			throw exception("Invalid GameState");
	}
}

void GameStateManager::KeyDown(int glfwKey)
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

bool GameStateManager::IsWinOrLose() const
{
	return m_gameState == GameState::Win || m_gameState == GameState::Lose;
}

void GameStateManager::IntroFinished()
{
	if(m_gameState == GameState::Intro)
	{
		m_gameState = GameState::Gameplay;
	}
}
