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
	levelMaps->SetCurrentLevelId(5);
	currentLevelTiles = levelMaps->GetLevelMapPointers();
	currentLevelColliders = levelMaps->GetLevelColliderPointers();

	player = new Player(screen, levelMaps);
}

int currentLevel = 0;
int tempCounter = 0;

void Game::Tick(float deltaTime)
{
	tempCounter++;

	if(GetAsyncKeyState(VK_F1) && tempCounter > 300)
	{
		tempCounter = 0;
		currentLevel = (currentLevel + 1) % TOTAL_LEVEL_MAPS;
		levelMaps->SetCurrentLevelId(currentLevel);
		currentLevelTiles = nullptr;
		currentLevelColliders = nullptr;
		currentLevelTiles = levelMaps->GetLevelMapPointers();
		currentLevelColliders = levelMaps->GetLevelColliderPointers();
		return;
	}

	tileMap->DrawLevel(currentLevelTiles);
#ifdef _PHYSICS_DEBUG
	tileMap->DrawLevel(currentLevelColliders);
#endif
	player->Tick(deltaTime);
	player->Draw();
}
