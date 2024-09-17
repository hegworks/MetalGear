// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

void Game::Init()
{
	tileSet = new TileSet();
	tileMap = new TileMap(screen, tileSet);

	levelMaps = new LevelMaps();
	currentLevelTiles = levelMaps->GetLevelMapPointers(0);
	currentLevelColliders = levelMaps->GetLevelColliderPointers(0);

	player = new Player(screen);
}

void Game::Tick(float deltaTime)
{
	tileMap->DrawLevel(currentLevelTiles);
	tileMap->DrawLevel(currentLevelColliders);
	player->Tick(deltaTime);
	player->Draw();
}
