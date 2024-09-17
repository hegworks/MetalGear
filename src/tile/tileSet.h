#pragma once

constexpr char* TILESET_ADDRESS = "assets/tiles/main-tileset.png";
constexpr int TILESET_WIDTH = 32;
constexpr int TILESET_HEIGHT = 32;
constexpr int TILESET_ROWS = 50;
constexpr int TILESET_COLUMNS = 50;

class TileSet
{
public:
	Surface* GetGraphic() const { return graphic; }

	TileSet();

private:
	Surface* graphic;
};
