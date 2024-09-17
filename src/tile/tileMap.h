#pragma once
#include "tileSet.h"

namespace Tmpl8
{
/// <summary>
/// TileMap class to handle multi-row, multi-column tile sets
/// </summary>
class TileMap
{
public:
	// Constructors and destructor
	TileMap(Surface* screen, TileSet* tileSet);
	~TileMap();

	// Methods
	void SetCurrentTile(int tileIndex);
	void DrawCurrentTile(int x, int y) const;
	void DrawLevel(int** levelMap);

	// Getters
	int GetTileWidth() const { return tileWidth; }
	int GetTileHeight() const { return tileHeight; }
	int GetRows() const { return rows; }
	int GetColumns() const { return columns; }
	Surface* GetSurface() const { return graphicSurface; }

private:
	// Attributes
	Surface* screen;
	Surface* graphicSurface; // The tileset image
	int tileWidth, tileHeight; // Size of a single tile
	int rows, columns; // Number of rows and columns in the tileset
	int currentTile; // Currently selected tile index
};
} // namespace Tmpl8
