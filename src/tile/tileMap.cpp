#include "precomp.h"
#include "tileMap.h"

#include "levelMap/levelMap.h"

using namespace Tmpl8;

/*
* REF: note that this class has been made using the help of the
* Sprite class which is part of the Tmpl8 library and also by using the ChatGPT.
* More detailed information can be found in the LL Week 1.
*/

// Constructor
TileMap::TileMap(Surface* screen, TileSet* tileSet)
	: graphicSurface(tileSet->GetGraphic()), tileWidth(TILESET_WIDTH), tileHeight(TILESET_HEIGHT),
	rows(TILESET_ROWS), columns(TILESET_COLUMNS), currentTile(0)
{
	this->screen = screen;
}

// Destructor
TileMap::~TileMap()
{
}

// Set the current tile index
void TileMap::SetCurrentTile(int tileIndex)
{
	currentTile = tileIndex;
}

// Draw the current tile at the specified position
void TileMap::DrawCurrentTile(int x, int y) const
{
	// Check if tile is within visible bounds
	if(x < -tileWidth || x >(screen->width + tileWidth)) return;
	if(y < -tileHeight || y >(screen->height + tileHeight)) return;

	// Calculate the tile's row and column in the tileset
	int tileRow = currentTile / columns;
	int tileCol = currentTile % columns;

	// Calculate the source x and y position in the tileset image
	int srcX = tileCol * tileWidth;
	int srcY = tileRow * tileHeight;

	// Clip drawing if necessary
	int x1 = x, x2 = x + tileWidth;
	int y1 = y, y2 = y + tileHeight;
	uint* src = graphicSurface->pixels + srcX + srcY * graphicSurface->width;
	if(x1 < 0) src += -x1, x1 = 0;
	if(x2 > screen->width) x2 = screen->width;
	if(y1 < 0) src += -y1 * graphicSurface->width, y1 = 0;
	if(y2 > screen->height) y2 = screen->height;
	uint* dest = screen->pixels;

	// ensure the tile is inside the visible area
	if(x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * screen->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		// iterate over each pixel of the tile to be drawn
		for(int j = 0; j < h; j++)
		{
			for(int i = 0; i < w; i++)
			{
				const uint c1 = *(src + i);
				if(c1 & 0xffffff) *(dest + addr + i) = c1;
			}
			addr += screen->width;
			src += graphicSurface->width; // Move to the next row in the tileset
		}
	}
}

/// Draw the full level map
/// @param target Surface to draw the level onto
/// @param levelMap 2D array of tile indices
void TileMap::DrawLevel(int** levelMap)
{
	for(int row = 0; row < LEVELMAP_ROWS; ++row)
	{
		for(int col = 0; col < LEVELMAP_COLS; ++col)
		{
			int tileIndex = levelMap[row][col];
			if(tileIndex != -1)
			{
				SetCurrentTile(tileIndex);
				DrawCurrentTile(col * tileWidth, row * tileHeight);
			}
		}
	}
}
