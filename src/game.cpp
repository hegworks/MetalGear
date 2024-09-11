// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "levelMap/levelMaps.h"
#include "tileMap.h"

const char* tileSetAddress = "assets/tiles/main-tileset.png";
const int tileWidth = 32;
const int tileHeight = 32;
const int tileSetRows = 50;
const int tileSetColumns = 50;


Surface* tileSet = nullptr;
TileMap* tileMap = nullptr;
LevelMaps* levelMaps = nullptr;
int** currentLevelPointers = nullptr;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	tileSet = new Surface(tileSetAddress);
	tileMap = new TileMap(tileSet, tileWidth, tileHeight, tileSetRows, tileSetColumns);

	levelMaps = new LevelMaps();
	currentLevelPointers = levelMaps->GetLevelMapPointers(0);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float /* deltaTime */)
{
	tileMap->DrawLevel(screen, currentLevelPointers, LevelMap::COLS, LevelMap::ROWS);
}
