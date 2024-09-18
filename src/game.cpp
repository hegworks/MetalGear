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
	levelMaps->SetCurrentLevelId(0);
	currentLevelTiles = levelMaps->GetLevelMapPointers();
	currentLevelColliders = levelMaps->GetLevelColliderPointers();

	player = new Player(screen, levelMaps);
}

void Game::Tick(float deltaTime)
{
	tileMap->DrawLevel(currentLevelTiles);
#ifdef _PHYSICS_DEBUG
	tileMap->DrawLevel(currentLevelColliders);
#endif
	player->Tick(deltaTime);
	player->Draw();
}
