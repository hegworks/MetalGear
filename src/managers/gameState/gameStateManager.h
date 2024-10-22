﻿#pragma once
#include "gameState.h"
#include "src/managers/room/roomChangeType.h"

class BulletManager;

namespace Tmpl8
{
class TileMap;
}

class EnemySpawner;
class LevelMaps;
class RoomFinder;
class Radio;
class LoseScreen;
class Player;
class WinScreen;

class GameStateManager
{
public:
	GameStateManager(Surface* pScreen, WinScreen* pWinScreen, LoseScreen* pLoseScreen, Player* pPlayer, Radio* pRadio, RoomFinder* pRoomFinder, LevelMaps* pLevelMaps, EnemySpawner* pEnemySpawner, TileMap* pTileMap, BulletManager* pBulletManager);
	void PassDownReport();
	void PassDownTick(float deltaTime);
	void ChangeGameStateBasedOnReports();
	void Tick(float deltaTime);
	void Draw() const;
	void DrawColliders() const;
	void HandleGameStateChangeBasedOnKeyDown(int glfwKey);
	void PassDownKeyDown(int glfwKey);
	void KeyDown(int glfwKey);
	void KeyUp(int glfwKey);
	GameState GetGameState() const { return m_gameState; }
	bool IsIntro() const { return m_gameState == GameState::Intro; }
	void ChangeRoom(RoomChangeType roomChangeType = RoomChangeType::None);

private:
	GameState m_gameState = GameState::Intro;

	Surface* m_pScreen = nullptr;
	WinScreen* m_pWinScreen = nullptr;
	LoseScreen* m_pLoseScreen = nullptr;
	Player* m_pPlayer = nullptr;
	Radio* m_pRadio = nullptr;
	RoomFinder* m_pRoomFinder = nullptr;
	LevelMaps* m_pLevelMaps = nullptr;
	EnemySpawner* m_pEnemySpawner = nullptr;
	TileMap* m_pTileMap = nullptr;
	BulletManager* m_pBulletManager = nullptr;

	int** m_ppCurrentLevelTiles = nullptr;
	int** m_ppCurrentLevelColliders = nullptr;

	const int RESTART_KEY = GLFW_KEY_R;
	const int RADIO_KEY = GLFW_KEY_F4;
};
