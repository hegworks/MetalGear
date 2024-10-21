#pragma once
#include "gameState.h"

class RoomFinder;
class Radio;
class LoseScreen;
class Player;
class WinScreen;

class GameStateManager
{
public:
	GameStateManager(Surface* pScreen, WinScreen* pWinScreen, LoseScreen* pLoseScreen, Player* pPlayer, Radio* pRadio, RoomFinder* pRoomFinder);
	void Tick(float deltaTime);
	void Draw() const;
	void KeyDown(int glfwKey);
	GameState GetGameState() const { return m_gameState; }
	bool IsWinOrLose() const;
	bool IsIntro() const { return m_gameState == GameState::Intro; }
	void IntroFinished();

private:
	GameState m_gameState = GameState::Intro;

	Surface* m_pScreen = nullptr;
	WinScreen* m_pWinScreen = nullptr;
	LoseScreen* m_pLoseScreen = nullptr;
	Player* m_pPlayer = nullptr;
	Radio* m_pRadio = nullptr;
	RoomFinder* m_pRoomFinder = nullptr;

	const int RESTART_KEY = GLFW_KEY_R;
	const int RADIO_KEY = GLFW_KEY_F4;
};
