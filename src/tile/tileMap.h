#pragma once

class TileSet;

namespace Tmpl8
{
/// <summary>
/// TileMap class to handle multi-row, multi-column tile sets
/// </summary>
class TileMap
{
public:
	TileMap(Surface* screen, const TileSet* tileSet);
	void DrawLevel(int** levelMap);

private:
	// Attributes
	Surface* screen;
	Surface* graphicSurface; // The tileset image
	int tileWidth, tileHeight; // Size of a single tile
	int rows, columns; // Number of rows and columns in the tileset
	int currentTile; // Currently selected tile index

	void DrawCurrentTile(int x, int y) const;
};
} // namespace Tmpl8
