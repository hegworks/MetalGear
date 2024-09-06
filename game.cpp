// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "tileMap.h"

int tileWidth = 16;
int tileHeight = 16;
int tileSetRows = 6;
int tileSetColumns = 7;

const int levelRows = 6;
const int levelColumns = 7;

int levelMap[levelRows][levelColumns] = {
    {3, 4, 5, 6, 37, 0, 0},
    {10, 11, 12, 13, 21, 0, 0},
    {17, 18, 19, 20, 21, 0, 0},
    {24, 25, 26, 27, 21, 0, 0},
    {22, 22, 22, 22, 21, 0, 0},
    {22, 22, 22, 22, 21, 0, 0}
};

int* levelMapPtrs[levelRows];
Surface* tileSet = nullptr;
TileMap* tileMap = nullptr;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
    tileSet = new Surface("assets/tiles/main-tileset2.png");

    // Initialize the level map pointers
    // each row is a pointer to the first column of the row
    for (int i = 0; i < levelRows; ++i)
    {
        levelMapPtrs[i] = levelMap[i];
    }

    tileMap = new TileMap(tileSet, tileWidth, tileHeight, tileSetRows, tileSetColumns);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float /* deltaTime */)
{
    tileMap->DrawLevel(screen, levelMapPtrs, levelColumns, levelRows);
}
