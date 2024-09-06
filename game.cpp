// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

Sprite* oneTileSprite;
Sprite* fiveTilesSprite;
const int tile_height = 16;
const int tile_width = 16;
int levelNumbers[10] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3};


// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
    oneTileSprite = new Sprite(new Surface("assets/tiles/oneTile.png"), 1);
    fiveTilesSprite = new Sprite(new Surface("assets/tiles/fiveTiles.png"), 5);
}

void DrawSprite(int spriteIndex, int screenTilePosX, int screenTilePosY, Surface* screen)
{
    fiveTilesSprite->SetFrame(spriteIndex);
    // draw the sprite at the given position on the screen
    fiveTilesSprite->Draw(screen, screenTilePosX * tile_width, screenTilePosY * tile_height);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float /* deltaTime */)
{
    // show oneTileSprite
    oneTileSprite->Draw(screen, 0, 0);

    // show fiveTilesSprite
    for (int i = 0; i < sizeof(levelNumbers) / sizeof(levelNumbers[0]); i++)
    {
        DrawSprite(levelNumbers[i], i, 0, screen);
    }
}
