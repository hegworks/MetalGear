// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
#include "managers/room/roomChangeType.h"

class TextRenderer;
class PixelPerfectCollisionChecker;
class LoseScreen;
class WinScreen;
class GameStateManager;
class BulletManager;
class EnemySpawner;
class Enemy;
class SpriteStorage;
class RoomChangeStorage;
class RoomFinder;
class Player;
class LevelMaps;
class TileSet;

namespace Tmpl8
{

class TileMap;

class Game : public TheApp
{
public:
	// game flow methods
	void Init();
	void Tick(float deltaTime);
	void Shutdown() { /* implement if you want to do something on exit */ }
	// input handling
	void MouseUp(int) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel(float) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp(int) { /* implement if you want to handle keys */ }
	void KeyDown(int glfwKey);
	// data members
	int2 mousePos;

private:
	TileSet* m_tileSet = nullptr;
	TileMap* m_tileMap = nullptr;
	LevelMaps* m_levelMaps = nullptr;
	int** m_currentLevelTiles = nullptr;
	int** m_currentLevelColliders = nullptr;
	Player* m_player = nullptr;
	RoomFinder* m_roomFinder = nullptr;
	RoomChangeStorage* m_roomChangeStorage = nullptr;
	SpriteStorage* m_spriteStorage = nullptr;
	EnemySpawner* m_enemySpawner = nullptr;
	BulletManager* m_bulletManager = nullptr;
	GameStateManager* m_gameStateManager = nullptr;
	WinScreen* m_winScreen = nullptr;
	LoseScreen* m_loseScreen = nullptr;
	PixelPerfectCollisionChecker* m_pixelPerfectCollisionChecker = nullptr;
	TextRenderer* m_textRendererFont = nullptr;
	TextRenderer* m_textRendererRadioNumbers = nullptr;

	void ChangeRoom(const RoomChangeType roomChangeType = RoomChangeType::None);
};

} // namespace Tmpl8