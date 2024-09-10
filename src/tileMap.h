#pragma once

namespace Tmpl8
{
/// <summary>
/// TileMap class to handle multi-row, multi-column tile sets
/// </summary>
class TileMap
{
public:
	// Constructors and destructor
	TileMap(Surface* surface, int tileWidth, int tileHeight, int rows, int columns);
	~TileMap();

	// Methods
	void SetCurrentTile(int tileIndex);
	void DrawCurrentTile(Surface* target, int x, int y);
	void DrawLevel(Surface* target, int** levelMap, int mapColumns, int mapRows);

	// Getters
	int GetTileWidth() const { return tileWidth; }
	int GetTileHeight() const { return tileHeight; }
	int GetRows() const { return rows; }
	int GetColumns() const { return columns; }
	Surface* GetSurface() const { return surface; }

private:
	// Attributes
	Surface* surface; // The tileset image
	int tileWidth, tileHeight; // Size of a single tile
	int rows, columns; // Number of rows and columns in the tileset
	int currentTile; // Currently selected tile index
};
} // namespace Tmpl8
