// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
#include "actors/human/enemy/enemy.h"
#include "actors/human/player/player.h"
#include "managers/enemy/enemySpawner.h"
#include "managers/room/roomFinder.h"
#include "tile/levelMap/levelMaps.h"
#include "tile/tileMap.h"
#include "tile/tileSet.h"

namespace Tmpl8
{

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
	void KeyDown(int) { /* implement if you want to handle keys */ }
	// data members
	int2 mousePos;

	TileSet* tileSet = nullptr;
	TileMap* tileMap = nullptr;
	LevelMaps* levelMaps = nullptr;
	int** currentLevelTiles = nullptr;
	int** currentLevelColliders = nullptr;
	Player* player = nullptr;
	RoomFinder* roomFinder = nullptr;
	RoomChangeStorage* roomChangeStorage = nullptr;
	SpriteStorage* spriteStorage;
	Enemy* enemy = nullptr;
	EnemySpawner* enemySpawner = nullptr;

	void ChangeRoom();
};

} // namespace Tmpl8