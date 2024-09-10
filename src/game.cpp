// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "LevelMap/levelMap.h"
#include "LevelMaps/levelMaps.h"
#include "tileMap.h"

const char* tileSetAddress = "assets/tiles/main-tileset.png";
const int tileWidth = 32;
const int tileHeight = 32;
const int tileSetRows = 50;
const int tileSetColumns = 50;

const int levelRows = 24;
const int levelColumns = 32;
int* levelMapPtrs[levelRows];
Surface* tileSet = nullptr;
TileMap* tileMap = nullptr;
LevelMap* lm = nullptr;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	tileSet = new Surface(tileSetAddress);


	// Initialize the level map pointers
	// each row is a pointer to the first column of the row
	for(int i = 0; i < levelRows; i++)
	{
		levelMapPtrs[i] = LevelMaps::levelMap0[i];
	}

	lm = new LevelMap(levelMapPtrs, levelRows, levelColumns);

	tileMap = new TileMap(tileSet, tileWidth, tileHeight, tileSetRows, tileSetColumns);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float /* deltaTime */)
{
	tileMap->DrawLevel(screen, lm->matrix, lm->columnCount, lm->rowCount);
}
