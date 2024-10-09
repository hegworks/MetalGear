#pragma once
#include "gameState.h"

class LoseScreen;
class Player;
class WinScreen;

class GameStateManager
{
public:
	GameStateManager(Surface* pScreen, WinScreen* pWinScreen, LoseScreen* pLoseScreen, Player* pPlayer);
	void Tick(float deltaTime);
	void Draw() const;
	void KeyDown(int glfwKey);
	GameState GetGameState() const { return m_gameState; }
	void IntroFinished();

private:
	GameState m_gameState = GameState::Intro;

	Surface* m_pScreen = nullptr;
	WinScreen* m_pWinScreen = nullptr;
	LoseScreen* m_pLoseScreen = nullptr;
	Player* m_pPlayer = nullptr;

	const int RESTART_KEY = GLFW_KEY_R;
};
