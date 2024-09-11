// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "actors/player.h"
#include "game.h"
#include "levelMap/levelMaps.h"
#include "tileMap.h"
#include "tileSet.h"

void Game::Init()
{
	tileSet = new Surface(TileSet::ADDRESS);
	tileMap = new TileMap(tileSet, TileSet::WIDTH, TileSet::HEIGHT, TileSet::ROWS, TileSet::COLUMNS);

	levelMaps = new LevelMaps();
	currentLevelPointers = levelMaps->GetLevelMapPointers(0);

	player = new Player();
}

void Game::Tick(float deltaTime)
{
	tileMap->DrawLevel(screen, currentLevelPointers, LevelMap::COLS, LevelMap::ROWS);
	player->Tick(deltaTime);
	player->Draw(screen);
}
